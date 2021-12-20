// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicBall.h"
#include "SevarogCharacter.h"
#include "PlayerBase.h"
// Sets default values
AMagicBall::AMagicBall()
{
	PrimaryActorTick.bCanEverTick = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	MySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MySphereComponent->InitSphereRadius(50.f);
	RootComponent = MySphereComponent;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> FireBall(TEXT("/Game/ParagonSevarog/FX/Particles/Abilities/SoulStackPassive/FX/P_ShadowTrailsCharSelect.P_ShadowTrailsCharSelect"));
	if (FireBall.Succeeded())
	{
		MagicBall = FireBall.Object;
	}

}

void AMagicBall::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorBeginOverlap.AddDynamic(this, &AMagicBall::OnOverlap);
}

// Called when the game starts or when spawned
void AMagicBall::BeginPlay()
{
	Super::BeginPlay();
	FVector vLoc = this->GetActorLocation();
	NewLoc = this->GetActorLocation();
	FVector vTargetLoc = Cast<APlayerBase>(GetWorld()->GetFirstPlayerController()->GetCharacter())->GetPlayerLocation();
	MoveDir = vTargetLoc - vLoc;
	MoveDir.Normalize();
	fSpeed = 50.f;

	GameStatic->SpawnEmitterAttached(MagicBall, RootComponent, NAME_None);

}

void AMagicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float random = FMath::RandRange(2, 10);
	NewLoc += MoveDir * DeltaTime * fSpeed * random;
	RootComponent->SetWorldLocation(NewLoc);
}

void AMagicBall::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{

	if (OtherActor != nullptr && OtherActor != this)
	{
		UE_LOG(LogClass, Warning, TEXT("Hit"));

		auto otherCharacter = Cast<APlayerBase>(OtherActor);
		if (!otherCharacter) return;

		UE_LOG(LogClass, Warning, TEXT("Col"));

		if (otherCharacter->GetHealth() <= 1.0f)
		{
			otherCharacter->UpdateHealth(-50.0f);
			Destroy();
		}

	}
}


