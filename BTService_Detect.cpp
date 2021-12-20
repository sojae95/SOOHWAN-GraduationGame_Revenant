// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "BossController.h"
#include "PlayerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect() 
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}


void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 1000.0f;

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
				
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABossController::TargetKey, PlayerBase);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, PlayerBase->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), PlayerBase->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
		
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABossController::TargetKey, nullptr);
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);

}
