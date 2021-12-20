// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FinalPro.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossSpawn.generated.h"

UCLASS()
class FINALPRO_API ABossSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BossSpawnMesh;

	UPROPERTY()
		class UParticleSystem* SpawnParticle;

	UPROPERTY()
		class UGameplayStatics* GameStatic;
};
