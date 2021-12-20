// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnimInstance.h"
#include "PlayerBase.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
    static ConstructorHelpers::FObjectFinder<UAnimMontage> FireShot(
        TEXT("/Game/ParagonRevenant/Characters/Heroes/Revenant/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage"));
    if (FireShot.Succeeded())
    {
        fireMontage = FireShot.Object;
    } 

    static ConstructorHelpers::FObjectFinder<UAnimMontage> Reload(
        TEXT("/Game/ParagonRevenant/Characters/Heroes/Revenant/Animations/RMB_Reload_Fast_Montage.RMB_Reload_Fast_Montage"));
    if (Reload.Succeeded())
    {
        reloadMontage = Reload.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> bloodBolt(
        TEXT("/Game/ParagonRevenant/Characters/Heroes/Revenant/Animations/RMB_Reload_Med_Montage.RMB_Reload_Med_Montage"));
    if (bloodBolt.Succeeded())
    {
        bloodBoltMontage = bloodBolt.Object;
    }


    static ConstructorHelpers::FObjectFinder<UAnimMontage>  bloodHealth(
        TEXT("/Game/ParagonRevenant/Characters/Heroes/Revenant/Animations/Cast_Montage.Cast_Montage"));
    if (bloodHealth.Succeeded())
    {
        bloodHealthMontage = bloodHealth.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage>  bloodHand(
        TEXT("/Game/ParagonRevenant/Characters/Heroes/Revenant/Animations/R_Ability_Montage.R_Ability_Montage"));
    if (bloodHand.Succeeded())
    {
        bloodHandMontage = bloodHand.Object;
    }

   
    forwardValue = 0.f;
    rightValue = 0.f;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    auto pawn = dynamic_cast<APlayerBase*>(TryGetPawnOwner());

    if (!::IsValid(pawn)) return;

    velocity = pawn->GetVelocity().Size();
    forwardValue = pawn->GetForwardValue();
    rightValue = pawn->GetRightValue();
}

void UPlayerAnimInstance::PlayFireMontage()
{
    if (IsAnyMontagePlaying()) return;
      Montage_Play(fireMontage, 1.0f);
}


void UPlayerAnimInstance::PlayReloadMontage()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(reloadMontage, 1.0f);
}

void UPlayerAnimInstance::PlayBloodBoltMontage()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(bloodBoltMontage, 1.0f);
}

void UPlayerAnimInstance::PlayBloodHealthMontage()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(bloodHealthMontage, 1.0f);
}

void UPlayerAnimInstance::PlayBloodHandMontage()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(bloodHandMontage, 1.0f);
}
