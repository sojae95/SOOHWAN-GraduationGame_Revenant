// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossTurn.h"
#include "PlayerBase.h"
#include "BossController.h"
#include "SevarogCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BossTurn::UBTTask_BossTurn()
{
	NodeName = TEXT("BossTurn");
}

EBTNodeResult::Type UBTTask_BossTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<ASevarogCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	auto Target = Cast<APlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABossController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - Monster->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Monster->SetActorRotation(FMath::RInterpTo(Monster->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
