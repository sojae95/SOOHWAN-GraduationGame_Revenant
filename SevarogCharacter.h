  // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SevarogCharacter.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMoveEndDelegate);

UCLASS()
class FINALPRO_API ASevarogCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASevarogCharacter();

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

public: 
	UPROPERTY()
		class USevarogAnimInstance* monsterAnim;

	UPROPERTY()
		class ABossController* monsterAI;

	UPROPERTY(VisibleAnyWhere, Category = Weapon)
		class USphereComponent* AttackingCol;

	UPROPERTY(VisibleAnyWhere, Category = MagicWeapon)
		class UCapsuleComponent* AttackingMagicCol;

	UPROPERTY(VisibleAnyWhere, Category = MagicHand)
		class UCapsuleComponent* AttackingMagicHandCol;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* overlapComp, AActor* otherActor, UPrimitiveComponent* otherComp,
			int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
		void OnMoveMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	FVector GetPlayerLocation() { return this->GetActorLocation(); }


	FOnAttackEndDelegate OnAttackEnd;
	FOnMoveEndDelegate OnMoveEnd;
public:
	void Attack();
	void FirstSkill();
	void SecondSkill();
	void ThirdSkill();
	void FourthSkill();
	void Strike();
	void Disappear();
	void Appear();
	void RadialDamage();
	void HandDamage(int iOnoff);
	void BeamDamage(int iOnoff);

private:
	void SeverServerApplyRadialDamage_Implementation(float Damage, float Radius);

private:
	bool IsAttacking;
	bool IsMoving;

};
