// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerBase.h"
#include "QuestNPC.h"
#include "DialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void QuestOneInteraction();
	void QuestOneFinishInteraction();
	void QuestTwoInteraction();
	void QuestNotInteraction();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MessageBackGround")
		class	UImage* MessageBackGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
		class	UTextBlock* QuestOneMessageBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
		class	UTextBlock* QuestTwoMessageBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
		class	UTextBlock* SoulCountMessageBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
		class	UTextBlock* SoulMessageBlock;
};
