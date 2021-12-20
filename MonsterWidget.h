// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FinalPro.h"
#include "Blueprint/UserWidget.h"
#include "MonsterWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API UMonsterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacter(class AMonsterBase* NewMonster);
	void BindStaticMesh(class ADummyTraining* NewActor);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class AMonsterBase> CurrentMon;
	TWeakObjectPtr<class ADummyTraining> CurrentActor;

	UPROPERTY()
		class UProgressBar* HPProgressBar;
};
