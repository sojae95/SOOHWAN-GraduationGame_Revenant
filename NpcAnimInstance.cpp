// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcAnimInstance.h"
#include "QuestNPC.h"

UNpcAnimInstance::UNpcAnimInstance()
{



}


void UNpcAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    auto pawn = dynamic_cast<AQuestNPC*>(TryGetPawnOwner());

    if (!::IsValid(pawn)) return;


 

}

