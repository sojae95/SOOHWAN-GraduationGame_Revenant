// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_LDCreateRandom.h"
#include "BossController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_LDCreateRandom::UBTService_LDCreateRandom()
{
	NodeName = TEXT("LDCreateRandomNum");
	Interval = 1.0f;

	bNotifyBecomeRelevant = true;
}

void UBTService_LDCreateRandom::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	int x = 0;
	x = FMath::RandRange(1, 100);



	if (x <= 15)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ABossController::SelectAttackNumber1, 1); // 15%
	}
	else if (x <= 40)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ABossController::SelectAttackNumber1, 2); // 25%
	}
	else if (x <= 65)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ABossController::SelectAttackNumber1, 3); // 25%
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ABossController::SelectAttackNumber1, 4); // 25%
	}

}
