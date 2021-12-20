// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MagicBall.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API UBTTask_MagicBall : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MagicBall();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool IsAttacking = false;

};
