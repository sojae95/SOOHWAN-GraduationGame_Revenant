// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "FinalPro.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DummyTraining.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS()
class FINALPRO_API ADummyTraining : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADummyTraining();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* DummyTrainingMesh;

	UPROPERTY(VisibleAnyWhere, Category = UI)
		class UWidgetComponent* HPBarWidget;

	void UpdateHealth(float HealthChange);
	void UpdateHealthTimer();
	float GetHealth();
	

	FOnHPChangedDelegate OnHPChanged;
	struct FTimerHandle HealthTimerHandle;

	float FullHealth;
	float Health;
	float HealthPercentage;
};
