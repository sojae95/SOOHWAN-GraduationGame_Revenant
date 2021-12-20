// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FinalPro.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class FINALPRO_API UMonsterAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    UMonsterAnimInstance();
    virtual void NativeUpdateAnimation(float deltaSeconds) override;
    void MonsterAttack();

private:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
        UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
        float velocity;
};
