// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogCharacter.h"
#include "FinalPro.h"
#include "BossController.h"
#include "SevarogAnimInstance.h"
#include "MagicBall.h"
#include "PlayerBase.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASevarogCharacter::ASevarogCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.0f, 0.f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BASE(
		TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Meshes/Sevarog.Sevarog"));

	if (SK_BASE.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BASE.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Game/AI/Monster/BP_AnimSevarog.BP_AnimSevarog_C"));
	if (anim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(anim.Class);
	}

	FName weapon_rSocket(TEXT("HammerSocket"));
	if (GetMesh()->DoesSocketExist(weapon_rSocket))
	{
		AttackingCol = CreateDefaultSubobject<USphereComponent>(TEXT("Weapon"));
		AttackingCol->SetCollisionProfileName(TEXT("OverlapAll"));
		AttackingCol->InitSphereRadius(50.0f);
		AttackingCol->SetupAttachment(GetMesh(), weapon_rSocket);
		AttackingCol->SetHiddenInGame(false);
	}

	FName weapon_Socket(TEXT("Chest"));
	if (GetMesh()->DoesSocketExist(weapon_Socket))
	{
		AttackingMagicCol = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MagicWeapon"));
		AttackingMagicCol->SetCollisionProfileName(TEXT("OverlapAll"));
		AttackingMagicCol->SetupAttachment(GetMesh(), weapon_Socket);
		AttackingMagicCol->SetHiddenInGame(true);
		AttackingMagicCol->SetRelativeLocationAndRotation(FVector(770.f, 0.f, -200.f), FRotator(80.f, 0.f, 0.0f));
		AttackingMagicCol->SetWorldScale3D(FVector(7.f, 3.f, 17.f));
		AttackingMagicCol->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	FName weapon_HandSocket(TEXT("Cast_L"));
	if (GetMesh()->DoesSocketExist(weapon_HandSocket))
	{
		AttackingMagicHandCol = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MagicHand"));
		AttackingMagicHandCol->SetCollisionProfileName(TEXT("OverlapAll"));
		AttackingMagicHandCol->SetupAttachment(GetMesh(), weapon_HandSocket);
		AttackingMagicHandCol->SetHiddenInGame(true);
		AttackingMagicHandCol->SetRelativeLocationAndRotation(FVector(90.f, 120.f, -70.f), FRotator(65.f, 0.f, 180.f));
		AttackingMagicHandCol->SetWorldScale3D(FVector(2.f, 2.f, 2.f));
		AttackingMagicHandCol->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	
	Tags.Add(FName("Monster"));

	AIControllerClass = ABossController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void ASevarogCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	monsterAI = Cast<ABossController>(GetController());

	if (monsterAI != nullptr)
	{
		monsterAI->StopAI();
		monsterAnim->BornBoss();

		FTimerHandle WaitHandle;
		float WaitTime = 5.2f; //시간을 설정하고
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			monsterAI->StartAI();
		}), WaitTime, false); //반복도 여기서 추가 변수를 선언해 설정가능시작 몽타주 재생후 패턴시작
	}
}


void ASevarogCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;


}

void ASevarogCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	monsterAnim = dynamic_cast<USevarogAnimInstance*>(GetMesh()->GetAnimInstance());
    monsterAnim->OnMontageEnded.AddDynamic(this, &ASevarogCharacter::OnAttackMontageEnded);
	monsterAnim->OnMontageEnded.AddDynamic(this, &ASevarogCharacter::OnMoveMontageEnded);


	AttackingCol->OnComponentBeginOverlap.AddDynamic(this, &ASevarogCharacter::OnOverlapBegin);
	AttackingMagicHandCol->OnComponentBeginOverlap.AddDynamic(this, &ASevarogCharacter::OnOverlapBegin);
	AttackingMagicCol->OnComponentBeginOverlap.AddDynamic(this, &ASevarogCharacter::OnOverlapBegin);

}

void ASevarogCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

void ASevarogCharacter::OnMoveMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsMoving = false;
	OnMoveEnd.Broadcast();
}

float ASevarogCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	return 0.0f;
}

void ASevarogCharacter::OnOverlapBegin(UPrimitiveComponent* overlapComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

// Called every frame
void ASevarogCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASevarogCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASevarogCharacter::Attack()
{
	if (IsAttacking) return;

	monsterAnim->PlayAttackMontage();
	IsAttacking = true;
}


void ASevarogCharacter::FirstSkill()
{
	if (IsAttacking) return;

	monsterAnim->PlayMagicSkillMontage();
	IsAttacking = true;

}

void ASevarogCharacter::SecondSkill()
{
	if (IsAttacking) return;

	monsterAnim->PlayMagicSkill1Montage();
	IsAttacking = true;
}

void ASevarogCharacter::ThirdSkill()
{
	if (IsAttacking) return;

	monsterAnim->PlayMagicSkill2Montage();
	IsAttacking = true;
}

void ASevarogCharacter::FourthSkill()
{
	if (IsAttacking) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FRotator rotator;
	FVector SpawnLocation = this->GetActorLocation();
	GetWorld()->SpawnActor<AMagicBall>(AMagicBall::StaticClass(), FVector(SpawnLocation.X - 300.0f, SpawnLocation.Y, SpawnLocation.Z), rotator, SpawnParams); // 왼쪽
	GetWorld()->SpawnActor<AMagicBall>(AMagicBall::StaticClass(), FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z + 300.0f), rotator, SpawnParams); // 위
	GetWorld()->SpawnActor<AMagicBall>(AMagicBall::StaticClass(), FVector(SpawnLocation.X + 300.0f, SpawnLocation.Y, SpawnLocation.Z), rotator, SpawnParams); // 오른쪽
	monsterAnim->PlayMagicSkill3Montage();
	IsAttacking = true;
}

void ASevarogCharacter::Strike()
{
	if (IsAttacking) return;

	monsterAnim->PlayStrikeAttack();
	IsAttacking = true;
}

void ASevarogCharacter::Disappear()
{
	if (IsMoving) return;

	monsterAnim->PlayDisappear();
	IsMoving = true;
}

void ASevarogCharacter::Appear()
{
	if (IsMoving) return;

	monsterAnim->PlayAppear();
	IsMoving = true;
}

void ASevarogCharacter::RadialDamage()
{
	SeverServerApplyRadialDamage_Implementation(200.0f * 2.0, 300);
}

void ASevarogCharacter::HandDamage(int iOnoff)
{
	if (iOnoff == 0)
	{
		AttackingMagicHandCol->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else if(iOnoff == 1)
	{
		AttackingMagicHandCol->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ASevarogCharacter::BeamDamage(int iOnoff)
{
	if (iOnoff == 0)
	{
		AttackingMagicCol->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else if (iOnoff == 1)
	{
		AttackingMagicCol->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ASevarogCharacter::SeverServerApplyRadialDamage_Implementation(float Damage, float Radius)
{

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, this->GetActorLocation(), Radius, nullptr, TArray<AActor*>(), this, this->GetController(),false, ECC_GameTraceChannel1);
	
	FVector Center = this->GetActorLocation();
	UWorld* World = GetWorld();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(Radius),
		CollisionQueryParam
	);


	DrawDebugSphere(World, Center, Radius, 16, FColor::Red, false, 0.2f);

	if (bResult)
	{
		for (auto OverlapResult : OverlapResults)
		{
			APlayerBase* Player = Cast<APlayerBase>(OverlapResult.GetActor());
			if (Player != nullptr)
			{
				/*CHECK(Player != nullptr);
				FVector PlayerLocation = Player->GetActorLocation();
				FTransform PlayerTransform = Player->GetActorTransform();
				if (!Player->IsDodge)
				{
					UGameplayStatics::PlaySoundAtLocation(this, GruxGroundHit, PlayerLocation);
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GruxFireEffect, PlayerTransform, true);
				}*/
			}
		}
	}

}

