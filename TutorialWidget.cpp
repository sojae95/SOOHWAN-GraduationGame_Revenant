// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MessageBackGround->SetVisibility(ESlateVisibility::Hidden);
	WelcomeMessageBlock->SetOpacity(0.0f);
	StartMessageBlock->SetOpacity(0.0f);
	MoveMessageBlock->SetOpacity(0.0f);
	ThankMessageBlock->SetOpacity(0.0f);
	Skill1MessageBlock->SetOpacity(0.0f);
	Skill2MessageBlock->SetOpacity(0.0f);
	Skill3MessageBlock->SetOpacity(0.0f);
	MoveNextMessageBlock->SetOpacity(0.0f);
	bIsStart = true;
	bIsHeal = true;
	bIsNext = false;
	bIsMoveCheck = false;
	bIsMoveNextStage = false;
	CoolTime = 2.0f;

	bIsMove.Init(false, 4);
	bIsSkillCheck.Init(false, 3);
	bIsGoodJob.Init(false, 4);
	MyCharacter = Cast<APlayerBase>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void UTutorialWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	//Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsStart)
	{
		if (CoolTime > 0.0f)
		{
			CoolTime -= InDeltaTime;

			if (MessageBackGround == nullptr) return;

			MessageBackGround->SetVisibility(ESlateVisibility::Visible);

			if (StartMessageBlock == nullptr) return;

			WelcomeMessageBlock->SetOpacity(1.0f);

			
		}
		else
		{
			MessageBackGround->SetVisibility(ESlateVisibility::Hidden);
			WelcomeMessageBlock->SetOpacity(0.0f);
			bIsStart = false;
			bIsNext = true;
			CoolTime = 2.0f;
		}
	}

	if (bIsNext)
	{
		if (CoolTime > 0.0f)
		{
			CoolTime -= InDeltaTime;

			if (MessageBackGround == nullptr) return;

			MessageBackGround->SetVisibility(ESlateVisibility::Visible);

			if (StartMessageBlock == nullptr) return;

			StartMessageBlock->SetOpacity(1.0f);


		}
		else
		{
			MessageBackGround->SetVisibility(ESlateVisibility::Hidden);
			StartMessageBlock->SetOpacity(0.0f);
			bIsNext = false;
			bIsMoveCheck = true;
			CoolTime = 2.0f;
		}
	}

	// Player Move Check 하는 부분
	if (bIsMoveCheck)
	{
		if (MessageBackGround == nullptr) return;

		MessageBackGround->SetVisibility(ESlateVisibility::Visible);

		if (StartMessageBlock == nullptr) return;

		MoveMessageBlock->SetOpacity(1.0f);

		if (MyCharacter->GetForwardValue() > 0.f)
			bIsMove[0] = true;
		if(MyCharacter->GetForwardValue() < 0.f)
			bIsMove[1] = true;
		if (MyCharacter->GetRightValue() > 0.f)
			bIsMove[2] = true;
		if (MyCharacter->GetRightValue() < 0.f)
			bIsMove[3] = true;

		if (bIsMove[0] == true && bIsMove[1] == true && bIsMove[2] == true && bIsMove[3] == true)
		{
			MoveMessageBlock->SetOpacity(0.0f);
			MessageBackGround->SetVisibility(ESlateVisibility::Hidden);
			bIsMoveCheck = false;
			bIsGoodJob[0] = true;
		}

	}

	// 잘했다고 하는 부분
	if (bIsGoodJob[0])
	{
		if (CoolTime > 0.0f)
		{
			CoolTime -= InDeltaTime;

			if (MessageBackGround == nullptr) return;

			MessageBackGround->SetVisibility(ESlateVisibility::Visible);

			if (StartMessageBlock == nullptr) return;

			ThankMessageBlock->SetOpacity(1.0f);


		}
		else
		{
			MessageBackGround->SetVisibility(ESlateVisibility::Hidden);
			ThankMessageBlock->SetOpacity(0.0f);
			bIsGoodJob[0] = false;
			bIsSkillCheck[0] = true;
			CoolTime = 2.0f;
		}
	}

	// 첫번째 스킬 쓰는거 확인
	if (bIsSkillCheck[0])
	{

		if (MessageBackGround == nullptr) return;

		MessageBackGround->SetVisibility(ESlateVisibility::Visible);

		if (StartMessageBlock == nullptr) return;

		Skill1MessageBlock->SetOpacity(1.0f);

		if (MyCharacter->GetPlayerWidget()->GetSkill1() && MyCharacter->GetTutorialCheck(0))
		{
			Skill1MessageBlock->SetOpacity(0.0f);
			MessageBackGround->SetVisibility(ESlateVisibility::Hidden);
			bIsGoodJob[1] = true;
			bIsSkillCheck[0] = false;
		}

	}

	if (bIsGoodJob[1])
	{
		if (CoolTime > 0.0f)
		{
			CoolTime -= InDeltaTime;

			if (MessageBackGround == nullptr) return;

			MessageBackGround->SetVisibility(ESlateVisibility::Visible);

			if (StartMessageBlock == nullptr) return;

			ThankMessageBlock->SetOpacity(1.0f);


		}
		else
		{
			MessageBackGround->SetVisibility(ESlateVisibility::Hidden);
			ThankMessageBlock->SetOpacity(0.0f);
			bIsGoodJob[1] = false;
			bIsSkillCheck[1] = true;
			CoolTime = 2.0f;
		}
	}

	// 두번째 스킬 쓰는거 확인
	if (bIsSkillCheck[1])
	{
		if (MessageBackGround == nullptr) return;

		MessageBackGround->SetVisibility(ESlateVisibility::Visible);

		if (StartMessageBlock == nullptr) return;

		Skill2MessageBlock->SetOpacity(1.0f);

		if (bIsHeal)
		{
			MyCharacter->UpdateHealth(-200);
			bIsHeal = false;
		}

		if (MyCharacter->GetPlayerWidget()->GetSkill2() && MyCharacter->GetTutorialCheck(1))
		{
			Skill2MessageBlock->SetOpacity(0.0f);
			Skill2MessageBlock->SetVisibility(ESlateVisibility::Hidden);
			bIsSkillCheck[1] = false;
			bIsGoodJob[2] = true;
		}

	}

	if (bIsGoodJob[2])
	{
		if (CoolTime > 0.0f)
		{
			CoolTime -= InDeltaTime;

			if (MessageBackGround == nullptr) return;

			MessageBackGround->SetVisibility(ESlateVisibility::Visible);

			if (StartMessageBlock == nullptr) return;

			ThankMessageBlock->SetOpacity(1.0f);


		}
		else
		{
			MessageBackGround->SetVisibility(ESlateVisibility::Hidden);
			ThankMessageBlock->SetOpacity(0.0f);
			bIsGoodJob[2] = false;
			bIsSkillCheck[2] = true;
			CoolTime = 3.0f;
		}
	}

	// 세번째 스킬 쓰는거 확인
	if (bIsSkillCheck[2])
	{


		if (MessageBackGround == nullptr) return;

		MessageBackGround->SetVisibility(ESlateVisibility::Visible);

		if (StartMessageBlock == nullptr) return;

		Skill3MessageBlock->SetOpacity(1.0f);

		if (MyCharacter->GetPlayerWidget()->GetSkill3() && MyCharacter->GetTutorialCheck(2))
		{
			Skill3MessageBlock->SetOpacity(0.0f);
			MessageBackGround->SetVisibility(ESlateVisibility::Hidden);
			bIsSkillCheck[2] = false; 
			bIsGoodJob[3] = true;
		}

	}

	if (bIsGoodJob[3])
	{
		if (CoolTime > 0.0f)
		{
			CoolTime -= InDeltaTime;

			if (MessageBackGround == nullptr) return;

			MessageBackGround->SetVisibility(ESlateVisibility::Visible);

			if (StartMessageBlock == nullptr) return;

			ThankMessageBlock->SetOpacity(1.0f);


		}
		else
		{
			MessageBackGround->SetVisibility(ESlateVisibility::Hidden);
			ThankMessageBlock->SetOpacity(0.0f);
			bIsGoodJob[3] = false;
			bIsMoveNextStage = true;
	        // 다음 튜토리얼 true 할꺼
			CoolTime = 2.0f;
		}
	}

	if (bIsMoveNextStage)
	{
		if (CoolTime > 0.0f)
		{
			CoolTime -= InDeltaTime;

			if (MessageBackGround == nullptr) return;

			MessageBackGround->SetVisibility(ESlateVisibility::Visible);

			if (StartMessageBlock == nullptr) return;

			MoveNextMessageBlock->SetOpacity(1.0f);


		}
		else
		{
			MessageBackGround->SetVisibility(ESlateVisibility::Hidden);
			MoveNextMessageBlock->SetOpacity(0.0f);
			bIsMoveNextStage = false;
			CoolTime = 2.0f;
		}
	}
	
	

}


