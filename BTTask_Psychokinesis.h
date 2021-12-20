// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Psychokinesis.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API UBTTask_Psychokinesis : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Psychokinesis();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool IsAttacking = false;
};
