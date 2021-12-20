// Fill out your copyright notice in the Description page of Project Settings.


#include "HpSoul.h"
#include "PlayerBase.h"

// Sets default values
AHpSoul::AHpSoul()
{
	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	MyBoxComponent->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	RootComponent = MyBoxComponent;


	//Soul = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("/Game/Realistic_Starter_VFX_Pack/Particles/Sparks/P_Sparks_E.P_Sparks_E"));
	//Soul->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//Soul->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> SoulHp(TEXT("/Game/Realistic_Starter_VFX_Pack/Particles/Sparks/P_Sparks_E.P_Sparks_E"));
	if (SoulHp.Succeeded())
	{
		Soul = SoulHp.Object;
	}

	
}

void AHpSoul::BeginPlay()
{
	Super::BeginPlay();

	GameStatic->SpawnEmitterAttached(Soul, RootComponent, NAME_None);

}


void AHpSoul::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorBeginOverlap.AddDynamic(this, &AHpSoul::OnOverlap);
}

void AHpSoul::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	//

	if (OtherActor != nullptr && OtherActor != this)
	{
		UE_LOG(LogClass, Warning, TEXT("Hit"));

		auto otherCharacter = Cast<APlayerBase>(OtherActor);
		if (!otherCharacter) return;

		UE_LOG(LogClass, Warning, TEXT("Col"));

		if (otherCharacter->GetHealth() <= 1.0f)
		{
			otherCharacter->AddSoulCount();
			otherCharacter->UpdateHealth(200.0f);
			Destroy();
		}
		
	}

}
