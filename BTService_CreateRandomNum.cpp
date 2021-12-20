 // Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CreateRandomNum.h"
#include "BossController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CreateRandomNum::UBTService_CreateRandomNum()
{
	NodeName = TEXT("CreateRandomNum");
	Interval = 1.0f;

	bNotifyBecomeRelevant = true;
}

void UBTService_CreateRandomNum::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	int x = 0;
	x = FMath::RandRange(1, 100);



	if (x <= 10)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ABossController::SelectAttackNumber, 1); // 10%
	}
	else if (x <= 20)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ABossController::SelectAttackNumber, 2); // 10%
	}
	else if (x <= 50)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ABossController::SelectAttackNumber, 3); // 30%
	}
	else if (x <= 80)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ABossController::SelectAttackNumber, 4); // 30%
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ABossController::SelectAttackNumber, 5); // 20%
	}

}