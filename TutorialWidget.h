// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerBase.h"
#include "TutorialWidget.generated.h"

UENUM()
enum class EGamePlayerMove
{
	ERight,
	ELeft,
	EFoward,
	EBack,
	EPlayerMove

};
/**
 * 
 */
UCLASS()
class FINALPRO_API UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MessageBackGround")
		class	UImage* MessageBackGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
		class	UTextBlock* WelcomeMessageBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
		class	UTextBlock* StartMessageBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
		class	UTextBlock* ThankMessageBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
		class	UTextBlock* MoveMessageBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
		class	UTextBlock* Skill1MessageBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
		class	UTextBlock* Skill2MessageBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
		class	UTextBlock* Skill3MessageBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
		class	UTextBlock* MoveNextMessageBlock;


private:
	APlayerBase* MyCharacter;

private:
	bool bIsStart;
	bool bIsNext;
	bool bIsMoveCheck;
	bool bIsHeal;
	bool bIsMoveNextStage;

	TArray <bool> bIsGoodJob;
	TArray <bool> bIsSkillCheck;
	TArray <bool> bIsMove;


	float CoolTime;
	
};
