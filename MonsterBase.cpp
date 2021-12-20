// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterBase.h"
#include "FinalPro.h"
#include "MonsterAIController.h"
#include "MonsterAnimInstance.h"
#include "PlayerBase.h"
#include "HpSoul.h"
#include "Components/WidgetComponent.h"
#include "MonsterWidget.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.0f, 0.f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BASE(
		TEXT("/Game/ParagonMorigesh/Characters/Heroes/Morigesh/Skins/DarkHeart/Meshes/Morigesh_DarkHeart.Morigesh_DarkHeart"));

	if (SK_BASE.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BASE.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Game/AI/Monster/BP_AnimMonster.BP_AnimMonster_C"));
	if (anim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(anim.Class);
	}

	
	HPBarWidget = CreateAbstractDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));

	HPBarWidget->SetupAttachment(GetMesh());

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/AI/Monster/BP_MonsterUI.BP_MonsterUI_C"));

	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.f, 50.0f));
		
	}

	//Class'/Script/FinalPro.HpSoul'


	///Game/Characters/Player/BP_AnimPlayer.BP_AnimPlayer_C
	///Game/AI/Monster/BP_MonsterUI.BP_MonsterUI_C

	
	FName weapon_rSocket(TEXT("Muzzle_01"));
	if (GetMesh()->DoesSocketExist(weapon_rSocket))
	{
		AttackingCol = CreateDefaultSubobject<USphereComponent>(TEXT("Weapon"));
		AttackingCol->SetCollisionProfileName(TEXT("OverlapAll"));
		AttackingCol->SetupAttachment(GetMesh(), weapon_rSocket);
		//AttackingCol->SetHiddenInGame(true);
	}

	//FName WeapoSocket(TEXT("Muzzle_01"));
	//if (GetMesh()->DoesSocketExist(WeapoSocket));
	//{
	//	GetMesh()->SetupAttachment(AttackingCol, WeapoSocket);
	//}

	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;



	

	//AIControllerClass->

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);



	IsAttacking = false;
}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	FullHealth = 200.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;

	auto CharacterWidget = Cast<UMonsterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget)
	{
		//UE_LOG(LogClass, Warning, TEXT("CheckMonsterHP1"));
		CharacterWidget->BindCharacter(this);
	}
	
	monsterAI = Cast<AMonsterAIController>(GetController());
	//UE_LOG(LogClass, Warning, TEXT("CheckMonsterHP"));

}

void AMonsterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	
	

}

void AMonsterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	monsterAnim = dynamic_cast<UMonsterAnimInstance*>(GetMesh()->GetAnimInstance());
	monsterAnim->OnMontageEnded.AddDynamic(this, &AMonsterBase::OnAttackMontageEnded);

	

	AttackingCol->OnComponentBeginOverlap.AddDynamic(this, &AMonsterBase::OnOverlapBegin);
	
	
}

float AMonsterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//UE_LOG(LogClass, Warning, TEXT("GetDamage"));
	UpdateHealth(-DamageAmount);
	return 0.0f;
}



// Called every frame
void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonsterBase::Attack()
{
	if (IsAttacking) return;

	monsterAnim->MonsterAttack();
	IsAttacking = true;
}

void AMonsterBase::Death()
{
	//UE_LOG(LogClass, Warning, TEXT("MonsterDie"));

	GetCharacterMovement()->SetMovementMode(MOVE_None);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackingCol->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	monsterAI->StopAi();
	HPBarWidget->DestroyComponent();
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetSimulatePhysics(true);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FRotator rotator;
	FVector  SpawnLocation = GetActorLocation();
	GetWorld()->SpawnActor<AHpSoul>(AHpSoul::StaticClass(), SpawnLocation, rotator, SpawnParams);
	
}

void AMonsterBase::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

void AMonsterBase::OnOverlapBegin(UPrimitiveComponent* overlapComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if ((otherActor != nullptr) && (otherActor != this) && otherComp)
	{

		UE_LOG(LogClass, Warning, TEXT("Monster Hit: %s"), *otherActor->GetName());
	
		auto otherCharacter = Cast<APlayerBase>(otherActor);
		if (!otherCharacter) return;
	
		UE_LOG(LogClass, Warning, TEXT("Col"));
		
		FDamageEvent damageEvent;

		otherActor->TakeDamage(50.f, damageEvent, GetController(), this);

	}
}

void AMonsterBase::UpdateHealth(float HealthChange)
{

		Health = FMath::Clamp(Health += HealthChange, 0.0f, FullHealth);
		HealthPercentage = Health / FullHealth;
		OnHPChanged.Broadcast();

		if (Health <= 0.1f)
		{
			Death();
		}
	
	//UE_LOG(LogClass, Warning, TEXT("CheckMonsterHP"));
}

float AMonsterBase::GetHealth()
{
	//UE_LOG(LogClass, Warning, TEXT("CheckMonsterHP"));
	return HealthPercentage;
}







