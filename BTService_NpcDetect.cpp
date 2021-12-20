// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_NpcDetect.h"
#include "NpcController.h"
#include "PlayerBase.h"
#include "DialogWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"


UBTService_NpcDetect::UBTService_NpcDetect()
{
	NodeName = TEXT("NpcDetect");
	Interval = 1.0f;
}

void UBTService_NpcDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 300.0f;

	if (nullptr == World) return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam);

	if (bResult)
	{
		for (auto OverlapResult : OverlapResults)
		{

			APlayerBase* PlayerBase = Cast<APlayerBase>(OverlapResult.GetActor());
			if (PlayerBase)
			{
				DialogWidget = PlayerBase->GetDialogWidget();

				if (PlayerBase->GetSoulCount() < 3)
				{
					DialogWidget->QuestOneInteraction();
				}
				else
				{
					DialogWidget->QuestOneFinishInteraction();
					DialogWidget->QuestTwoInteraction();
				}

				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ANpcController::TargetKey, PlayerBase);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, PlayerBase->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), PlayerBase->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}

	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ANpcController::TargetKey, nullptr);
		if (DialogWidget != nullptr)
			DialogWidget->QuestNotInteraction();
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}