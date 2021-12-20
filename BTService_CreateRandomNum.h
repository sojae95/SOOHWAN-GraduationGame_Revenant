// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CreateRandomNum.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API UBTService_CreateRandomNum : public UBTService
{
	GENERATED_BODY()
	
		UBTService_CreateRandomNum();

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
