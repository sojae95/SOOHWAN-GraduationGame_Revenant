// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_LDCreateRandom.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API UBTService_LDCreateRandom : public UBTService
{
	GENERATED_BODY()

		UBTService_LDCreateRandom();

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
