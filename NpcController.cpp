// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ANpcController::TargetKey(TEXT("Target"));

ANpcController::ANpcController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/NPC/NPC_BB.Npc_BB"));

	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;

	}
	

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/NPC/Npc_BHT.Npc_BHT"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void ANpcController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		//Blackboard->SetValueAsVector(FowardVector, InPawn->GetActorForwardVector());
		if (!RunBehaviorTree(BTAsset))
		{
			//ABLOG()
		}
	}
}