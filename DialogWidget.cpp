// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MessageBackGround->SetVisibility(ESlateVisibility::Hidden);
	QuestOneMessageBlock->SetOpacity(0.0f);
	QuestTwoMessageBlock->SetOpacity(0.0f);
	SoulCountMessageBlock->SetOpacity(0.0f);
	SoulMessageBlock->SetOpacity(0.0f);
}

void UDialogWidget::QuestOneInteraction()
{
	if (MessageBackGround == nullptr) return;

		MessageBackGround->SetVisibility(ESlateVisibility::Visible);

	if (QuestOneMessageBlock == nullptr) return;

		QuestOneMessageBlock->SetOpacity(1.0f);

	if (SoulCountMessageBlock == nullptr) return;

		SoulCountMessageBlock->SetOpacity(1.0f);

	if (SoulMessageBlock == nullptr) return;

		SoulMessageBlock->SetOpacity(1.0f);
}

void UDialogWidget::QuestOneFinishInteraction()
{
	if (MessageBackGround == nullptr) return;

	MessageBackGround->SetVisibility(ESlateVisibility::Visible);

	if (SoulCountMessageBlock == nullptr) return;

	SoulCountMessageBlock->SetOpacity(0.0f);

	if (SoulMessageBlock == nullptr) return;

	SoulMessageBlock->SetOpacity(0.0f);
}

void UDialogWidget::QuestTwoInteraction()
{
	if (MessageBackGround == nullptr) return;

	MessageBackGround->SetVisibility(ESlateVisibility::Visible);

	if (QuestTwoMessageBlock == nullptr) return;

	QuestTwoMessageBlock->SetOpacity(1.0f);

}

void UDialogWidget::QuestNotInteraction()
{
	if (MessageBackGround == nullptr) return;

	MessageBackGround->SetVisibility(ESlateVisibility::Hidden);

	if (QuestOneMessageBlock == nullptr) return;

	QuestOneMessageBlock->SetOpacity(0.0f);

	if (QuestOneMessageBlock == nullptr) return;

	QuestTwoMessageBlock->SetOpacity(0.0f);
}




