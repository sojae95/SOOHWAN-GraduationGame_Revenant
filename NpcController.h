// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NpcController.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API ANpcController : public AAIController
{
	GENERATED_BODY()

public:
	ANpcController();
	

	virtual void OnPossess(APawn* InPawn) override;
	static const FName TargetKey;

private:

	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
};
