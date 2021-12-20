// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FinalPro.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API UBTDecorator_IsAttackRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


};
