// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FinalPro.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRO_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
    UPlayerAnimInstance();
    virtual void NativeUpdateAnimation(float deltaSeconds) override;
    void PlayFireMontage();
    void PlayReloadMontage();
    void PlayBloodBoltMontage();
    void PlayBloodHealthMontage();
    void PlayBloodHandMontage();

private:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Fire, Meta = (AllowPrivateAccess = true))
        UAnimMontage* fireMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Fire, Meta = (AllowPrivateAccess = true))
        UAnimMontage* reloadMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
        UAnimMontage* bloodBoltMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
        UAnimMontage* bloodHealthMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
        UAnimMontage* bloodHandMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
        float forwardValue;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
        float rightValue;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
        float velocity;

};
