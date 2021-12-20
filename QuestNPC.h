// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "QuestNPC.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInteractionEndDelegate);

UCLASS()
class FINALPRO_API AQuestNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQuestNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
		class UNpcAnimInstance* NpcAnim;

	UPROPERTY()
		class ANpcController* NpcAI;

	FOnInteractionEndDelegate OnInteractionEnd;

private:
	bool IsInteracting;
};
