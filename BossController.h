// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossController.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API ABossController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABossController();
	void StopAI();
	void StartAI();

	virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;
	//static const FName FowardVector;
	static const FName TargetKey;
	static const FName Distance;
	static const FName SelectAttackNumber;
	static const FName SelectAttackNumber1;

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
};
