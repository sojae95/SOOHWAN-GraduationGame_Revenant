// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveFront.h"
#include "BossController.h"
#include "SevarogCharacter.h"

UBTTask_MoveFront::UBTTask_MoveFront()
{
	bNotifyTick = true;
	IsMoving = false;
}

EBTNodeResult::Type UBTTask_MoveFront::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto BossBase = Cast<ASevarogCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == BossBase)
		return EBTNodeResult::Failed;

	BossBase->Appear();
	IsMoving = true;
	BossBase->OnMoveEnd.AddLambda([this]() -> void {IsMoving = false; });

	return EBTNodeResult::InProgress;
}

void UBTTask_MoveFront::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsMoving)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
