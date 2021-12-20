// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SevarogAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API USevarogAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    USevarogAnimInstance();
    virtual void NativeUpdateAnimation(float deltaSeconds) override;
    void PlayMagicSkillMontage();
    void PlayAttackMontage();
    void PlayStrikeAttack();
    void PlayMagicSkill1Montage();
    void PlayMagicSkill2Montage();
    void PlayMagicSkill3Montage();
    void BornBoss();
    void PlayDisappear();
    void PlayAppear();

private:
    UFUNCTION()
        void AnimNotify_BackMove();

    UFUNCTION()
        void AnimNotify_FrontMove();

    UFUNCTION()
        void AnimNotify_RadialDamage();

    UFUNCTION()
        void AnimNotify_BeamDamage();

    UFUNCTION()
        void AnimNotify_BeamFinish();

    UFUNCTION()
        void AnimNotify_HandDamage();

    UFUNCTION()
        void AnimNotify_HandFinish();

  


private:
    bool bIsFirst = false;


    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Create, Meta = (AllowPrivateAccess = true))
        UAnimMontage* BornMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
        UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
        UAnimMontage* MagicMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
        UAnimMontage* MagicHandMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
        UAnimMontage* MagicBallMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Strike, Meta = (AllowPrivateAccess = true))
        UAnimMontage* StrikeMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
        UAnimMontage* PsyMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Move, Meta = (AllowPrivateAccess = true))
        UAnimMontage* DisappearMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Move, Meta = (AllowPrivateAccess = true))
        UAnimMontage* AppearMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
        float velocity;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
        FVector fowardvec;
};
