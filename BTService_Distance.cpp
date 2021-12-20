// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Distance.h"
#include "BossController.h"
#include "SevarogCharacter.h"
#include "PlayerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Distance::UBTService_Distance()
{
	NodeName = TEXT("Distance");
	Interval = 1.0f;
	
}

void UBTService_Distance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	auto Sevarog = Cast<ASevarogCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	bool bResult;

	auto Target = Cast<APlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABossController::TargetKey));

	if (nullptr == Target)
		return;

	bResult = (Target->GetDistanceTo(ControllingPawn) > 700.0f);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABossController::Distance, bResult);

}