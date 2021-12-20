// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Turn.h"
#include "PlayerBase.h"
#include "MonsterBase.h"
#include "MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
	
UBTTask_Turn::UBTTask_Turn()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_Turn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonsterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	auto Target = Cast<APlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - Monster->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Monster->SetActorRotation(FMath::RInterpTo(Monster->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
