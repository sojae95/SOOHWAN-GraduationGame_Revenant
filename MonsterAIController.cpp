// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


const FName AMonsterAIController::HomePosKey(TEXT("HomePos"));
const FName AMonsterAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AMonsterAIController::TargetKey(TEXT("Target"));

AMonsterAIController::AMonsterAIController()
{
	//RepeatInterval = 3.0f;
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/Monster/Monster_BB.Monster_BB"));

	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;

	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/Monster/Monster_BHT.Monster_BHT"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}




}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			//ABLOG()
		}
	}

	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this,
	//	&ATestAIController::OnReapeatTimer, RepeatInterval, true);
}

void AMonsterAIController::StopAi()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

//void ATestAIController::OnUnPossess()
//{
//	Super::OnUnPossess();
//	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
//}

//void ATestAIController::OnReapeatTimer()
//{
//	auto CurrentPawn = GetPawn();
//	if (CurrentPawn == nullptr) return;
//
//	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
//	if (nullptr == NavSystem) return;
//
//	FNavLocation NextLocation;
//	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
//	{
//		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
//		
//	}
//
//}
