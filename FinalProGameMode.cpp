// Copyright Epic Games, Inc. All Rights Reserved.

#include "FinalProGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"


AFinalProGameMode::AFinalProGameMode()
	: Super()
{

	PrimaryActorTick.bCanEverTick = true;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/FinalPro.PlayerBase"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	UiWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SkillUi"));

	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBar(TEXT("/Game/Ui/BP_PlayerUI.BP_PlayerUI_C"));
	HUDWidgetClass = HealthBar.Class;

	// use our custom HUD class
	//HUDClass = FinalProHUD::StaticClass();
	
	// add Health Bar UI to viewport
	if (HUDWidgetClass != nullptr)
	{
		UiWidget->SetWidgetClass(HUDWidgetClass);
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget)
		{
			
			//CurrentWidget->AddToViewport();
			
		}
	}

	UIDialogWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DialogUi"));

	static ConstructorHelpers::FClassFinder<UUserWidget> Dialog(TEXT("/Game/Ui/BP_Dialog.BP_Dialog_C"));
	DialogWidgetClass = Dialog.Class;

	if (DialogWidgetClass != nullptr)
	{
		UIDialogWidget->SetWidgetClass(DialogWidgetClass);
		DialogCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), DialogWidgetClass);

		if (DialogCurrentWidget)
		{

			//CurrentWidget->AddToViewport();

		}
	}

	CoolTime = 5.0f;
	
}

void AFinalProGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentState(EGamePlayState::EPlaying);

	MyCharacter = Cast<APlayerBase>(UGameplayStatics::GetPlayerPawn(this, 0));
	MyCharacter->SetUserWidget(UiWidget);
	MyCharacter->SetDialogWidget(UIDialogWidget);
	
}


void AFinalProGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyCharacter)
	{
		if (FMath::IsNearlyZero(MyCharacter->GetHealth(), 0.001f))
		{
			if (CoolTime > 0.0f)
			{
				CoolTime -= DeltaTime;
			}
			else
			{
				SetCurrentState(EGamePlayState::EGameOver);
				CoolTime = 5.0f;
			}
		}
	}

}

EGamePlayState AFinalProGameMode::GetCurrentState() const
{
	return CurrentState;
}

void AFinalProGameMode::SetCurrentState(EGamePlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

void AFinalProGameMode::HandleNewState(EGamePlayState NewState)
{
	switch (NewState)
	{
	case EGamePlayState::EPlaying:
	{
		// do nothing
	}
	break;
	// Unknown/default state
	case EGamePlayState::EGameOver:
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
	break;
	// Unknown/default state
	default:
	case EGamePlayState::EUnknown:
	{
		// do nothing
	}
	break;
	}
}

