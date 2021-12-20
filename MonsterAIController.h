// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FinalPro.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMonsterAIController();


	virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

	void StopAi();

private:
	/*void OnReapeatTimer();

	FTimerHandle RepeatTimerHandle;

	float RepeatInterval;*/

	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
};
