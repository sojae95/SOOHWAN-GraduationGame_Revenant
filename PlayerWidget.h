// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
			class	UImage* SkillBloodBolt;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
			class	UImage* SkillBloodHealth;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
			class	UImage* BuffBloodHealth;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
			class	UImage* SkillBloodHand;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
			class	UImage* BuffBloodHand;

		void SetSkill1(bool bIsCan) { bIsCanSkill1 = bIsCan; }
		void SetSkill2(bool bIsCan) { bIsCanSkill2 = bIsCan; }
		void SetSkill3(bool bIsCan) { bIsCanSkill3 = bIsCan; }
		void SetBuff1(bool bIsCan, float fcoolTime) { bIsCanBuff1 = bIsCan; fCoolTimeBuff1 = fcoolTime; }
		void SetBuff2(bool bIsCan, float fcoolTime) { bIsCanBuff2 = bIsCan; fCoolTimeBuff2 = fcoolTime; }
		bool GetSkill1() { return bIsCanSkill1; }
		bool GetSkill2() { return bIsCanSkill2; }
		bool GetSkill3() { return bIsCanSkill3; }
		bool GetBuff1() { return bIsCanBuff1; }
		bool GetBuff2() { return bIsCanBuff2; }

private:
		float fCoolTimeSkill1;
		float fCoolTimeSkill2;
		float fCoolTimeSkill3;
		float fCoolTimeBuff1;
		float fCoolTimeBuff2;
		bool bIsCanSkill1;
		bool bIsCanSkill2;
		bool bIsCanSkill3;
		bool bIsCanBuff1;
		bool bIsCanBuff2;
};
