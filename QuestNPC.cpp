// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestNPC.h"
#include "NpcAnimInstance.h"
#include "NpcController.h"

// Sets default values
AQuestNPC::AQuestNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.0f, 0.f));
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BASE(
        TEXT("/Game/ParagonSparrow/Characters/Heroes/Sparrow/Skins/Raven/Meshes/Sparrow_Raven.Sparrow_Raven"));

    if (SK_BASE.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(SK_BASE.Object);
    }

    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    static ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Game/AI/NPC/BP_AnimNpc.BP_AnimNpc_C"));
    if (anim.Succeeded())
    {
        GetMesh()->SetAnimInstanceClass(anim.Class);
    }


    AIControllerClass = ANpcController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();

    NpcAI = Cast<ANpcController>(GetController());
	
}

void AQuestNPC::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    NpcAnim = dynamic_cast<UNpcAnimInstance*>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AQuestNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQuestNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

