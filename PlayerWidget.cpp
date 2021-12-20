// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Components/Image.h"


void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();


	 fCoolTimeSkill1 = 7.0f;
	 fCoolTimeSkill2 = 10.0f;
	 fCoolTimeSkill3 = 20.0f;
	 fCoolTimeBuff1 = 30.0f;
	 fCoolTimeBuff2 = 15.0f;
	 bIsCanSkill1 = false;
	 bIsCanSkill2 = false;
	 bIsCanSkill3 = false;
	 bIsCanBuff1 = false;
	 bIsCanBuff2 = false;

	 BuffBloodHealth->SetVisibility(ESlateVisibility::Hidden);
	 BuffBloodHand->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsCanSkill1)
	{
		if (fCoolTimeSkill1 > 0.0f)
		{
			fCoolTimeSkill1 -= InDeltaTime;

			if (SkillBloodBolt == nullptr) return;

			SkillBloodBolt->GetDynamicMaterial()->SetScalarParameterValue("Percent", fCoolTimeSkill1 / 7.f);
		}
		else
		{
			bIsCanSkill1 = false;
			fCoolTimeSkill1 = 7.0f;
		}
	}
	
	if (bIsCanSkill2)
	{
		if (fCoolTimeSkill2 > 0.0f)
		{
			fCoolTimeSkill2 -= InDeltaTime;

			if (SkillBloodHealth == nullptr) return;

			SkillBloodHealth->GetDynamicMaterial()->SetScalarParameterValue("Percent", fCoolTimeSkill2 / 10.f);
		}
		else
		{
			bIsCanSkill2 = false;
			fCoolTimeSkill2 = 10.0f;
		}
	}

	if (bIsCanSkill3)
	{
		if (fCoolTimeSkill3 > 0.0f)
		{
			fCoolTimeSkill3 -= InDeltaTime;

			if (SkillBloodHand == nullptr) return;

			SkillBloodHand->GetDynamicMaterial()->SetScalarParameterValue("Percent", fCoolTimeSkill3 / 20.f);
		}
		else
		{
			bIsCanSkill3 = false;
			fCoolTimeSkill3 = 20.0f;
		}
	}

	if (bIsCanBuff1)
	{
		if (fCoolTimeBuff1 > 0.0f)
		{
			fCoolTimeBuff1 -= InDeltaTime;

			if (BuffBloodHealth == nullptr) return;

			BuffBloodHealth->SetVisibility(ESlateVisibility::Visible);

			BuffBloodHealth->GetDynamicMaterial()->SetScalarParameterValue("Percent", fCoolTimeBuff1 / 30.f);
		}
		else
		{
			BuffBloodHealth->SetVisibility(ESlateVisibility::Hidden);
			bIsCanBuff1 = false;
			fCoolTimeBuff1 = 30.0f;
		}
	}

	if (bIsCanBuff2)
	{
		if (fCoolTimeBuff2 > 0.0f)
		{
			fCoolTimeBuff2 -= InDeltaTime;

			if (BuffBloodHand == nullptr) return;

			BuffBloodHand->SetVisibility(ESlateVisibility::Visible);

			BuffBloodHand->GetDynamicMaterial()->SetScalarParameterValue("Percent", fCoolTimeBuff2 / 15.f);
		}
		else
		{
			BuffBloodHand->SetVisibility(ESlateVisibility::Hidden);
			bIsCanBuff2 = false;
			fCoolTimeBuff1 = 15.0f;
		}
	}

}
