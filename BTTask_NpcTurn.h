// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_NpcTurn.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API UBTTask_NpcTurn : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_NpcTurn();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
