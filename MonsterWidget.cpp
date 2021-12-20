// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterWidget.h"
#include "MonsterBase.h"
#include "DummyTraining.h"
#include "Components/ProgressBar.h"

void UMonsterWidget::BindCharacter(class AMonsterBase* NewMonster)
{
	
	if(nullptr == NewMonster)
		return;
				

	CurrentMon = NewMonster;
	//CurrentMon->OnHPChanged.AddLambda([this]() -> void { 
	//
	//	if (CurrentMon.IsValid())
	//	{
	//		CurrentMon->GetHealth();
	//	}
	//
	//});

	NewMonster->OnHPChanged.AddUObject(this, &UMonsterWidget::UpdateHPWidget);

}

void UMonsterWidget::BindStaticMesh(class ADummyTraining* NewActor)
{

	if (nullptr == NewActor)
		return;


	CurrentActor = NewActor;
	//CurrentMon->OnHPChanged.AddLambda([this]() -> void { 
	//
	//	if (CurrentMon.IsValid())
	//	{
	//		CurrentMon->GetHealth();
	//	}
	//
	//});

	NewActor->OnHPChanged.AddUObject(this, &UMonsterWidget::UpdateHPWidget);

}

void UMonsterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MonsterHPBar")));
	if (nullptr != HPProgressBar)
	{
		UpdateHPWidget();
	}



}

void UMonsterWidget::UpdateHPWidget()
{

	if (CurrentMon.IsValid())
	{
		
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentMon->GetHealth());
		}
	}

	if (CurrentActor.IsValid())
	{

		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentActor->GetHealth());
		}
	}

}
