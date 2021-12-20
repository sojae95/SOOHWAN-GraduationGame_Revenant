// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerBase.h"
#include "FinalProGameMode.generated.h"


UENUM()
enum class EGamePlayState
{
	EPlaying,
	EGameOver,
	EUnknown

};

UCLASS(minimalapi)
class AFinalProGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFinalProGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	APlayerBase* MyCharacter;


	/** Returns the current playing state */
	UFUNCTION(BlueprintPure, Category = "Health")
		EGamePlayState GetCurrentState() const;

	/** Sets a new playing state */
	void SetCurrentState(EGamePlayState NewState);

	UPROPERTY(EditAnywhere, Category = "Health")
		TSubclassOf<class UUserWidget> HUDWidgetClass;


	UPROPERTY(EditAnywhere, Category = "Health")
		class UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, Category = "Health")
		class UWidgetComponent* UiWidget;

	UPROPERTY(EditAnywhere, Category = "Dialog")
		TSubclassOf<class UUserWidget> DialogWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Dialog")
		class UUserWidget* DialogCurrentWidget;

	UPROPERTY(EditAnywhere, Category = "Dialog")
		class UWidgetComponent* UIDialogWidget;

private:
	/**Keeps track of the current playing state */
	EGamePlayState CurrentState;
	float CoolTime;

	/**Handle any function calls that rely upon changing the playing state of our game */
	void HandleNewState(EGamePlayState NewState);
};



