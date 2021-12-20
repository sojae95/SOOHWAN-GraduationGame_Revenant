// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
 DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS()
class FINALPRO_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack();
	void Death();

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* overlapComp, AActor* otherActor, UPrimitiveComponent* otherComp,
			int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void UpdateHealth(float HealthChange);
	float GetHealth();


	FOnAttackEndDelegate OnAttackEnd;
	FOnHPChangedDelegate OnHPChanged;

private:
	UPROPERTY()
		class UMonsterAnimInstance* monsterAnim;

	UPROPERTY()
		class AMonsterAIController* monsterAI;

	UPROPERTY(VisibleAnyWhere, Category = weapon)
		USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleAnyWhere, Category = Weapon)
		class USphereComponent* AttackingCol;

	UPROPERTY(VisibleAnyWhere, Category = UI)
		class UWidgetComponent* HPBarWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> HpSoul;

private:
	bool IsAttacking;

	float FullHealth;
	float Health;
	float HealthPercentage;
};
