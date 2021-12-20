// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NpcTurn.h"
#include "PlayerBase.h"
#include "NpcController.h"
#include "QuestNPC.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_NpcTurn::UBTTask_NpcTurn()
{
	NodeName = TEXT("NPCTurn");
}

EBTNodeResult::Type UBTTask_NpcTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto NPC = Cast<AQuestNPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == NPC)
		return EBTNodeResult::Failed;

	auto Target = Cast<APlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ANpcController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - NPC->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	NPC->SetActorRotation(FMath::RInterpTo(NPC->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}