// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FinalPro.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/Image.h"
#include "PlayerBase.generated.h"

class UInputComponent;
class UTimelineComponent;
class UPlayerWidget;
class UDialogWidget;

UCLASS()
class FINALPRO_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

		
public:
	// Sets default values for this character's properties
	APlayerBase();

	UPROPERTY(VisibleAnywhere, Category = "camera")
		USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = "camera")
		UCameraComponent* camera;

	UPROPERTY()
	   class UPlayerAnimInstance* playerAnim;

	UPROPERTY(EditAnywhere, Category = "UI")
		class UWidgetComponent* CurrentWidget;

	UPROPERTY(EditAnywhere, Category = "Dialog")
		class UWidgetComponent* DialogCurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float FullMagic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		float Magic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		float MagicPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		float PreviousMagic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		float MagicValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		bool redFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		UCurveFloat* MagicCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Die")
		bool bIsDieUi;

	float CurveFloatValue;
	float TimelineValue;
	bool bCanUseMagic;
	bool bCanBeDamaged;

	UTimelineComponent* MyTimeline;
	struct FTimerHandle MemberTimerHandle;
	struct FTimerHandle MagicTimerHandle;

	/** Get Health */
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	/** Get Magic */
	UFUNCTION(BlueprintPure, Category = "Magic")
		float GetMagic();

	/** Get Health Text */
	UFUNCTION(BlueprintPure, Category = "Health")
		FText GetHealthIntText();

	/** Get Magic Text */
	UFUNCTION(BlueprintPure, Category = "Magic")
		FText GetMagicIntText();

	UFUNCTION(BlueprintPure, Category = "Magic")
		FText GetSoulIntText();

	/** Damage Timer */
	UFUNCTION()
		void DamageTimer();

	/** Set Damage State */
	UFUNCTION()
		void SetDamageState();

	/** Set Magic Value */
	UFUNCTION()
		void SetMagicValue();

	/** Set Damage State */
	UFUNCTION()
		void SetMagicState();

	/** Set Damage State */
	UFUNCTION()
		void SetMagicChange(float MagicChange);

	/** Set Damage State */
	UFUNCTION()
		void UpdateMagic();

	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateHealth(float HealthChange);

	/** Play Flash */
	UFUNCTION(BlueprintPure, Category = "Health")
		bool PlayFlash();

	UFUNCTION(BlueprintPure, Category = "Die")
		bool PlayYouDie();

	UPROPERTY(EditAnywhere, Category = "Magic")
		class UMaterialInterface* GunDefaultMaterial;

	UPROPERTY(EditAnywhere, Category = "Magic")
		class UMaterialInterface* GunOverheatMaterial;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

	UPROPERTY()
		class UParticleSystem* FireParticle;

	UPROPERTY()
		class UParticleSystem* HealParticle;
	
	UPROPERTY()
		class UParticleSystem* BloodParticle;

	UPROPERTY()
		class UParticleSystem* SmokeParticle;

	UPROPERTY()
		class UParticleSystem* BloodBoltParticle;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class USoundCue* EmptyManaSoundCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class UAudioComponent* EmptyManaAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class USoundCue* HurtSoundCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class UAudioComponent* HurtAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class USoundCue* GunSoundCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class UAudioComponent* GunAudioComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetUserWidget(UWidgetComponent* userwidget) { CurrentWidget = userwidget; }
	void SetDialogWidget(UWidgetComponent* userwidget) { DialogCurrentWidget = userwidget; }
	void AddSoulCount() { SoulCount++; }

	float GetForwardValue() { return fowardValue; }
	float GetRightValue() { return rightValue; }
	bool  GetTutorialCheck(int iNum) { return bIsTutorialCheck[iNum]; }
	FVector GetPlayerLocation() { return this->GetActorLocation();}
	UPlayerWidget* GetPlayerWidget() { return PlayerWidget; }
	UDialogWidget* GetDialogWidget() { return DialogWidget; }
	int32 GetSoulCount() { return SoulCount; }


private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);

	void Fire();
	void SkillBloodBolt();
	void SkillBloodHealth();
	void SkillBloodHand();
	void Shot();
	void PlayerDie();


	float fowardValue = 0.f; 
	float rightValue = 0.f;
	int32 SoulCount = 0;

	UPlayerWidget* PlayerWidget;
	UDialogWidget* DialogWidget;
	bool bIsSkillBloodBolt;
	TArray <bool> bIsTutorialCheck;
};
