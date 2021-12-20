// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "MonsterBase.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
    static ConstructorHelpers::FObjectFinder<UAnimMontage> MonsterAttack(
        TEXT("/Game/ParagonMorigesh/Characters/Heroes/Morigesh/Animations/PrimaryAttack_A_Slow_Montage.PrimaryAttack_A_Slow_Montage"));
    if (MonsterAttack.Succeeded())
    {
        AttackMontage = MonsterAttack.Object;
    }



    velocity = 0;
}


void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    auto pawn = dynamic_cast<AMonsterBase*>(TryGetPawnOwner());

    if (!::IsValid(pawn)) return;


    velocity = pawn->GetVelocity().Size();

}

void UMonsterAnimInstance::MonsterAttack()
{
    if (IsAnyMontagePlaying()) return;
    Montage_Play(AttackMontage, 1.0f);
}




