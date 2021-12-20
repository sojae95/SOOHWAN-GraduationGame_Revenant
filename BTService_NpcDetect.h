// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_NpcDetect.generated.h"

class UDialogWidget;
/**
 * 
 */
UCLASS()
class FINALPRO_API UBTService_NpcDetect : public UBTService
{
	GENERATED_BODY()


public:
	UBTService_NpcDetect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UDialogWidget* DialogWidget;
};
