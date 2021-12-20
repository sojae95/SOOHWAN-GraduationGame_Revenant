// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Distance.h"
#include "BossController.h"
#include "PlayerBase.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_Distance::UBTDecorator_Distance()
{
	NodeName = TEXT("Distance");
}

bool UBTDecorator_Distance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<APlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABossController::TargetKey));
	if (nullptr == Target)
		return false;

	//auto Target = Cast<APlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::TargetKey));
	//if (nullptr == Target)
	//	return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) >= 700.0f);
	return bResult;

}
