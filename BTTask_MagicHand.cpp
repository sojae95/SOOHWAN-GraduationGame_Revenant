// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MagicHand.h"
#include "BossController.h"
#include "SevarogCharacter.h"

UBTTask_MagicHand::UBTTask_MagicHand()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_MagicHand::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto BossBase = Cast<ASevarogCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == BossBase)
		return EBTNodeResult::Failed;

	BossBase->ThirdSkill();
	IsAttacking = true;
	BossBase->OnAttackEnd.AddLambda([this]() -> void {IsAttacking = false; });

	return EBTNodeResult::InProgress;
}

void UBTTask_MagicHand::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		auto BossBase = Cast<ASevarogCharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if (nullptr == BossBase)
			return;

		BossBase->HandDamage(1);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
