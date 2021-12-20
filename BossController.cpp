// Fill out your copyright notice in the Description page of Project Settings.


#include "BossController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

//const FName ABossController::FowardVector(TEXT("FowardVector"));
const FName ABossController::TargetKey(TEXT("Target"));
const FName ABossController::Distance(TEXT("Distance"));
const FName ABossController::SelectAttackNumber(TEXT("SelectAttackNumber"));
const FName ABossController::SelectAttackNumber1(TEXT("SelectAttackNumber1"));

ABossController::ABossController()
{
	//RepeatInterval = 3.0f;
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/Monster/Boss_BB.Boss_BB"));

	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;

	}


	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/Monster/Boss_BHT.Boss_BHT"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

}

void ABossController::OnPossess(APawn* InPawn)
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

void ABossController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

void ABossController::StartAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StartTree(*this->BTAsset, EBTExecutionMode::Looped);
	}
}
