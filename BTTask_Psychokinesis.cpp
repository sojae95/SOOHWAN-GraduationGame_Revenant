// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Psychokinesis.h"
#include "BossController.h"
#include "SevarogCharacter.h"

UBTTask_Psychokinesis::UBTTask_Psychokinesis()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_Psychokinesis::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto BossBase = Cast<ASevarogCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == BossBase)
		return EBTNodeResult::Failed;

	BossBase->SecondSkill();
	IsAttacking = true;
	BossBase->OnAttackEnd.AddLambda([this]() -> void {IsAttacking = false; });

	return EBTNodeResult::InProgress;
}

void UBTTask_Psychokinesis::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
