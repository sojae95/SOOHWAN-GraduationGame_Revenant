// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogAnimInstance.h"
#include "SevarogCharacter.h"

USevarogAnimInstance::USevarogAnimInstance()
{
    static ConstructorHelpers::FObjectFinder<UAnimMontage> BornBossMontage(
        TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Animations/LevelStart_Montage.LevelStart_Montage"));
    if (BornBossMontage.Succeeded())
    {
        BornMontage = BornBossMontage.Object;
    }
  
    static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackBossMontage(
        TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Animations/Swing3_Slow_120fps_Montage.Swing3_Slow_120fps_Montage"));
    if (AttackBossMontage.Succeeded())
    {
        AttackMontage = AttackBossMontage.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> MagicHandBossMontage(
        TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Animations/Ultimate_Targeting_Montage.Ultimate_Targeting_Montage"));
    if (MagicHandBossMontage.Succeeded())
    {
        MagicHandMontage = MagicHandBossMontage.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> MagicBallBossMontage(
        TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Animations/Ultimate_Targeting_Montage1.Ultimate_Targeting_Montage1"));
    if (MagicBallBossMontage.Succeeded())
    {
        MagicBallMontage = MagicBallBossMontage.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> MagicBossMontage(
        TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Animations/Recall_Montage.Recall_Montage"));
    if (MagicBossMontage.Succeeded())
    {
        MagicMontage = MagicBossMontage.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> Magic1BossMontage(
        TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Animations/Subjugation_Montage.Subjugation_Montage"));
    if (Magic1BossMontage.Succeeded())
    {
        PsyMontage = Magic1BossMontage.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> StrikeBossMontage(
        TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Animations/Ultimate_Swing_120fps_Montage.Ultimate_Swing_120fps_Montage"));
    if (StrikeBossMontage.Succeeded())
    {
        StrikeMontage = StrikeBossMontage.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> DisappearMoveMontage(
        TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Animations/Disappear_Montage.Disappear_Montage"));
    if (DisappearMoveMontage.Succeeded())
    {
        DisappearMontage = DisappearMoveMontage.Object;
    }



    static ConstructorHelpers::FObjectFinder<UAnimMontage> AppearMoveMontage(
        TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Animations/Appear_Montage.Appear_Montage"));
    if (AppearMoveMontage.Succeeded())
    {
        AppearMontage = AppearMoveMontage.Object;
    }
  
  

    velocity = 0;
    fowardvec = FVector(0.0f, 0.0f, 0.0f);
   
}

void USevarogAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    auto pawn = dynamic_cast<ASevarogCharacter*>(TryGetPawnOwner());

   
    //if (!bIsFirst)
    //{
    //    BornBoss();
    //    bIsFirst = true;
    //}

    if (!::IsValid(pawn)) return;

    velocity = pawn->GetVelocity().Size();
    fowardvec = pawn->GetActorForwardVector();

}

void USevarogAnimInstance::PlayMagicSkillMontage()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(MagicMontage, 1.5f);
}

void USevarogAnimInstance::PlayAttackMontage()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(AttackMontage, 0.8f);
}

void USevarogAnimInstance::PlayStrikeAttack()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(StrikeMontage, 0.8f);
}

void USevarogAnimInstance::PlayMagicSkill1Montage()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(PsyMontage, 1.0f);
}

void USevarogAnimInstance::PlayMagicSkill2Montage()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(MagicHandMontage, 0.55f);
}

void USevarogAnimInstance::PlayMagicSkill3Montage()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(MagicBallMontage, 0.55f);
}

void USevarogAnimInstance::BornBoss()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(BornMontage, 1.0f);
}

void USevarogAnimInstance::PlayDisappear()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(DisappearMontage, 1.0f);
}

void USevarogAnimInstance::PlayAppear()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(AppearMontage, 1.0f);
}

void USevarogAnimInstance::AnimNotify_BackMove()
{
    auto pawn = dynamic_cast<ASevarogCharacter*>(TryGetPawnOwner());

    if (nullptr == pawn)
        return;
  
    FVector backvec = -fowardvec ; 
    
    pawn->SetActorRelativeLocation(pawn->GetActorLocation() + (backvec * 500));

}

void USevarogAnimInstance::AnimNotify_FrontMove()
{
    auto pawn = dynamic_cast<ASevarogCharacter*>(TryGetPawnOwner());

    if (nullptr == pawn)
        return;

   

    pawn->SetActorRelativeLocation(pawn->GetActorLocation() + (fowardvec * 500));

}

void USevarogAnimInstance::AnimNotify_RadialDamage()
{
    auto pawn = dynamic_cast<ASevarogCharacter*>(TryGetPawnOwner());

    if (nullptr == pawn)
        return;

    pawn->RadialDamage();

}

void USevarogAnimInstance::AnimNotify_BeamDamage()
{
    auto pawn = dynamic_cast<ASevarogCharacter*>(TryGetPawnOwner());

    if (nullptr == pawn)
        return;

    pawn->BeamDamage(0);

}

void USevarogAnimInstance::AnimNotify_BeamFinish()
{
    auto pawn = dynamic_cast<ASevarogCharacter*>(TryGetPawnOwner());

    if (nullptr == pawn)
        return;

    pawn->BeamDamage(1);

}

void USevarogAnimInstance::AnimNotify_HandDamage()
{
    auto pawn = dynamic_cast<ASevarogCharacter*>(TryGetPawnOwner());

    if (nullptr == pawn)
        return;

    pawn->HandDamage(0);

}

void USevarogAnimInstance::AnimNotify_HandFinish()
{
    auto pawn = dynamic_cast<ASevarogCharacter*>(TryGetPawnOwner());

    if (nullptr == pawn)
        return;

    //pawn->HandDamage(1);

}



