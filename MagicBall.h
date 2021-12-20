// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FinalPro.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicBall.generated.h"

UCLASS()
class FINALPRO_API AMagicBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicBall();

public:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		class UParticleSystem* MagicBall;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

	UPROPERTY(EditAnywhere)
		USphereComponent* MySphereComponent;

private: 
	FVector MoveDir;
	FVector NewLoc;
	float fSpeed;
};
