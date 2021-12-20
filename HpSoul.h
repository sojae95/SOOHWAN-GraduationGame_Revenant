// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FinalPro.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HpSoul.generated.h"

UCLASS()
class FINALPRO_API AHpSoul : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHpSoul();

public:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Soul;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

	UPROPERTY(EditAnywhere)
		UBoxComponent* MyBoxComponent;
};
