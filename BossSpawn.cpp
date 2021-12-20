// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSpawn.h"
#include "SevarogCharacter.h"



// Sets default values
ABossSpawn::ABossSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BossSpawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BossSpawn"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Spawn(TEXT("/Game/ParagonSevarog/FX/Particles/Abilities/Ultimate/FX/P_UltActivate.P_UltActivate"));
	if (Spawn.Succeeded())
	{
		SpawnParticle = Spawn.Object;
	}


}

// Called when the game starts or when spawned
void ABossSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

float ABossSpawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//UE_LOG(LogClass, Warning, TEXT("GetDamage"));


	GameStatic->SpawnEmitterAtLocation(GetWorld(),SpawnParticle, FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 200.f));

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FRotator rotator;
	GetWorld()->SpawnActor<ASevarogCharacter>(ASevarogCharacter::StaticClass(), FVector(GetActorLocation().X, GetActorLocation().Y , GetActorLocation().Z + 200.f), rotator, SpawnParams);

	Destroy();

	return 0.0f;
}

// Called every frame
void ABossSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

