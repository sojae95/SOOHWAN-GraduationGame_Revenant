// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StrikeAttack.h"
#include "BossController.h"
#include "SevarogCharacter.h"

UBTTask_StrikeAttack::UBTTask_StrikeAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_StrikeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto BossBase = Cast<ASevarogCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == BossBase)
		return EBTNodeResult::Failed;

	BossBase->Strike();
	IsAttacking = true;
	BossBase->OnAttackEnd.AddLambda([this]() -> void {IsAttacking = false; });

	return EBTNodeResult::InProgress;
}

void UBTTask_StrikeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}