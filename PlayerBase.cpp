// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"
#include "PlayerAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Components/TimelineComponent.h"
#include "Sound/SoundCue.h"
#include "DrawDebugHelpers.h" // 라인트레이스 를 위한 디버그
#include "Components/WidgetComponent.h"
#include "PlayerWidget.h"
#include "DialogWidget.h"

// Sets default values
APlayerBase::APlayerBase()
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));

    springArm->SetupAttachment(GetCapsuleComponent());
    camera->SetupAttachment(springArm);

    

    springArm->TargetArmLength = 450.f;
    springArm->SetRelativeLocation(FVector(80.f, 50.f, 80.f));
    springArm->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));

   

    springArm->bUsePawnControlRotation = true;


    bIsTutorialCheck.Init(false, 3);

    GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.0f, 0.f));
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BASE(
        TEXT("/Game/ParagonRevenant/Characters/Heroes/Revenant/Meshes/Revenant.Revenant"));

    if (SK_BASE.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(SK_BASE.Object);
    }

    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    static ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Game/Characters/Player/BP_AnimPlayer.BP_AnimPlayer_C"));
    if (anim.Succeeded())
    {
        GetMesh()->SetAnimInstanceClass(anim.Class);
    }

  

    static ConstructorHelpers::FObjectFinder<UParticleSystem> Fire(TEXT("/Game/ParagonRevenant/FX/Particles/Revenant/Abilities/Primary/FX/P_Revenant_Primary_MuzzleFlash.P_Revenant_Primary_MuzzleFlash"));
    if (Fire.Succeeded())
    {
        FireParticle = Fire.Object;
    }

    static ConstructorHelpers::FObjectFinder<UParticleSystem> Heal(TEXT("/Game/ParagonSevarog/FX/Particles/Abilities/SoulStackPassive/FX/P_SoulStageEmbers.P_SoulStageEmbers"));
    if (Heal.Succeeded())
    {
        HealParticle = Heal.Object;
    }

    static ConstructorHelpers::FObjectFinder<UParticleSystem> BloodBolt(TEXT("/Game/ParagonRevenant/FX/Particles/Revenant/Abilities/Mark/FX/P_Revenant_Mark_Hit.P_Revenant_Mark_Hit"));
    if (BloodBolt.Succeeded())
    {
        BloodBoltParticle = BloodBolt.Object;
    }

  
    static ConstructorHelpers::FObjectFinder<UParticleSystem> Blood(TEXT("/Game/Realistic_Starter_VFX_Pack/Particles/Hit/P_Blood.P_Blood"));
    if (Fire.Succeeded())
    {
        BloodParticle = Blood.Object;
    }
   
    static ConstructorHelpers::FObjectFinder<UParticleSystem> Smoke(TEXT("/Game/Realistic_Starter_VFX_Pack/Particles/Hit/P_Rock.P_Rock"));
    if (Fire.Succeeded())
    {
        SmokeParticle = Smoke.Object;
    }
    ///Game/ParagonRevenant/Audio/Cues/Revenant_Ability_LowMana.Revenant_Ability_LowMana

    static ConstructorHelpers::FObjectFinder<USoundCue> Empty(TEXT("/Game/ParagonRevenant/Audio/Cues/Revenant_Ability_LowMana.Revenant_Ability_LowMana"));
    if (Empty.Succeeded())
    {
        EmptyManaSoundCue = Empty.Object;

        EmptyManaAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("EmptyManaAudioComponent"));
        EmptyManaAudioComponent->SetupAttachment(RootComponent);
    }

    static ConstructorHelpers::FObjectFinder<USoundCue> Gun(TEXT("/Game/Characters/Player/GunSound/GunSound.GunSound"));
    if (Gun.Succeeded())
    {
        GunSoundCue = Gun.Object;

        GunAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("GunAudioComponent"));
        GunAudioComponent->SetupAttachment(RootComponent);
    }

    static ConstructorHelpers::FObjectFinder<USoundCue> Pain(TEXT("/Game/ParagonRevenant/Audio/Cues/Revenant_Effort_Pain.Revenant_Effort_Pain"));
    if (Pain.Succeeded())
    {
        HurtSoundCue = Pain.Object;

        HurtAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("HurtAudioComponent"));
        HurtAudioComponent->SetupAttachment(RootComponent);
    }
}

void APlayerBase::UpdateHealth(float HealthChange)
{
    Health = FMath::Clamp(Health += HealthChange, 0.0f, FullHealth);
    HealthPercentage = Health / FullHealth;
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
    
    PlayerWidget = Cast<UPlayerWidget>(CurrentWidget->GetUserWidgetObject());
    PlayerWidget->AddToViewport();

    DialogWidget = Cast<UDialogWidget>(DialogCurrentWidget->GetUserWidgetObject());
    DialogWidget->AddToViewport();
   

    FullHealth = 1000.0f;
    Health = FullHealth;
    HealthPercentage = 1.0f;
    bCanBeDamaged = true;

    FullMagic = 100.0f;
    Magic = FullMagic;
    MagicPercentage = 1.0f;
    PreviousMagic = MagicPercentage;
    MagicValue = 0.0f;
    bCanUseMagic = true;
    redFlash = false;
    bIsDieUi = false;

    bIsSkillBloodBolt = false;

    if (EmptyManaAudioComponent && EmptyManaSoundCue)
    {
        EmptyManaAudioComponent->SetSound(EmptyManaSoundCue);
    }

    if (GunAudioComponent && GunSoundCue)
    {
        GunAudioComponent->SetSound(GunSoundCue);
    }

    if (HurtAudioComponent && HurtSoundCue)
    {
        HurtAudioComponent->SetSound(HurtSoundCue);
    }

    if (MagicCurve)
    {
        FOnTimelineFloat TimelineCallback;
        FOnTimelineEventStatic TimelineFinishedCallback;

        TimelineCallback.BindUFunction(this, FName("SetMagicValue"));
        TimelineFinishedCallback.BindUFunction(this, FName("SetMagicState"));

        MyTimeline = NewObject<UTimelineComponent>(this, FName("Magic Animation"));
        MyTimeline->AddInterpFloat(MagicCurve, TimelineCallback);
        MyTimeline->SetTimelineFinishedFunc(TimelineFinishedCallback);
        MyTimeline->RegisterComponent();
    
    }

    APlayerController* PlayerController = Cast<APlayerController>(Controller);
    if (PlayerController)
    {
        if (PlayerController->PlayerCameraManager)
        {
            PlayerController->PlayerCameraManager->ViewPitchMin = -20.0; // Use whatever values you want
            PlayerController->PlayerCameraManager->ViewPitchMax = 10.0;
        }
    }
}

void APlayerBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    playerAnim = dynamic_cast<UPlayerAnimInstance*>(GetMesh()->GetAnimInstance());

    //playerAnimInstance->OnMontageEnded.AddDynamic(this, &APlayerBase::OnMontageEnded);
}

float APlayerBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    if (Health >= 0.f && bCanBeDamaged)
    {
        bCanBeDamaged = false;
        redFlash = true;
        UpdateHealth(-DamageAmount);
        DamageTimer();
        //if(health)
        if (HurtAudioComponent && HurtSoundCue)
        {
            HurtAudioComponent->Play(0.f);
        }
    }

    return DamageAmount;
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (MyTimeline != nullptr) MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
}


// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerBase::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerBase::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &APlayerBase::LookUp);
    PlayerInputComponent->BindAxis("Turn", this, &APlayerBase::Turn);

   PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &APlayerBase::Fire);
   PlayerInputComponent->BindAction(TEXT("BloodBolt"), EInputEvent::IE_Pressed, this, &APlayerBase::SkillBloodBolt);
   PlayerInputComponent->BindAction(TEXT("BloodHealth"), EInputEvent::IE_Pressed, this, &APlayerBase::SkillBloodHealth);
   PlayerInputComponent->BindAction(TEXT("BloodHand"), EInputEvent::IE_Pressed, this, &APlayerBase::SkillBloodHand);
   PlayerInputComponent->BindAction(TEXT("YouDie"), EInputEvent::IE_Pressed, this, &APlayerBase::PlayerDie);
}

void APlayerBase::MoveForward(float value)
{
    //UE_LOG(LogClass, Warning, TEXT("Forward %f"), value);
    AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::X), value);
    fowardValue = value;
}
void APlayerBase::MoveRight(float value)
{
    AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y), value);
    rightValue = value;
}
void APlayerBase::LookUp(float value)
{
    

    AddControllerPitchInput(value);
}
void APlayerBase::Turn(float value)
{
    AddControllerYawInput(value);
}

void APlayerBase::Fire()
{
    //!FMath::IsNearlyZero(Magic, 0.001f)
    if (Magic >= 20.0f && bCanUseMagic)
    {
       
         playerAnim->PlayFireMontage();
        
     

        if (GunAudioComponent && GunSoundCue)
        {
            GunAudioComponent->Play(0.f);
        }

        Shot();


        GameStatic->SpawnEmitterAttached(FireParticle, GetMesh(), FName("Muzzle_02"));

        if (MyTimeline != nullptr) MyTimeline->Stop();
        GetWorldTimerManager().ClearTimer(MagicTimerHandle);
        if (!PlayerWidget->GetBuff2())
        {
            SetMagicChange(-20.0f);
            bIsTutorialCheck[0] = true;
        }
        else
        {
            bIsTutorialCheck[2] = true;
        }
        GetWorldTimerManager().SetTimer(MagicTimerHandle, this, &APlayerBase::UpdateMagic, 4.0f, false);


    }
    else if(Magic < 1.0f)
    {
        if (EmptyManaAudioComponent && EmptyManaSoundCue)
        {
            EmptyManaAudioComponent->Play(0.f);
        }
    }
}

void APlayerBase::SkillBloodBolt()
{   
    if (!PlayerWidget->GetSkill1())
    {
        PlayerWidget->SetSkill1(true);
        bIsSkillBloodBolt = true;
        playerAnim->PlayBloodBoltMontage();
    }
}

void APlayerBase::SkillBloodHealth()
{
    if (!PlayerWidget->GetSkill2())
    {
        PlayerWidget->SetSkill2(true);
        PlayerWidget->SetBuff1(true, 30.0f);
        playerAnim->PlayBloodHealthMontage(); 
    }
}

void APlayerBase::SkillBloodHand()
{
    if (!PlayerWidget->GetSkill3())
    {
        PlayerWidget->SetSkill3(true);
        PlayerWidget->SetBuff2(true, 15.0f);
        playerAnim->PlayBloodHandMontage();
    }
}

void APlayerBase::Shot()
{
    FHitResult OutHit;
    FVector Start = FVector(springArm->GetComponentLocation().X, springArm->GetComponentLocation().Y, springArm->GetComponentLocation().Z + 25.f);


    FVector ForwardVector = GetControlRotation().Vector();
    FVector End = ((ForwardVector * 100000.f) + Start);
    FCollisionQueryParams CollisionParams;

    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

    if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
    {
        //DrawDebugSolidBox(GetWorld(), OutHit.ImpactPoint, FVector(10.f), FColor::Blue, true); // 디버그박스
        //UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *OutHit.GetActor()->GetName()); // 맞은 액터 이름 출력
        //UE_LOG(LogTemp, Log, TEXT("Hit Bone : %s"), *OutHit.BoneName.ToString()); // 맞은 Bone이름 출력

        if (OutHit.GetActor()->ActorHasTag("Monster"))
        {
            DrawDebugSolidBox(GetWorld(), OutHit.ImpactPoint, FVector(10.f), FColor::Blue, true); // 디버그박스
            //UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *OutHit.GetActor()->GetName()); // 맞은 액터 이름 출력
            //UE_LOG(LogTemp, Log, TEXT("Hit Bone : %s"), *OutHit.BoneName.ToString()); // 맞은 Bone이름 출력

            AActor* HitActor = OutHit.GetActor();
            FDamageEvent damageEvent;
            //UGameplayStatics::ApplyPointDamage(HitActor, 50.0f, HitActor->GetActorLocation(), OutHit, nullptr, this, nullptr);
            HitActor->TakeDamage(50.f, damageEvent, GetController(), this);
            
            if (PlayerWidget->GetBuff1())
            {
                GameStatic->SpawnEmitterAttached(HealParticle, GetMesh());
                UpdateHealth(10.0f);
                bIsTutorialCheck[1] = true;

            }

            if (bIsSkillBloodBolt == true)
            {
                UGameplayStatics::ApplyRadialDamage(GetWorld(), 100.0f, OutHit.ImpactPoint, 300.0f, nullptr, TArray<AActor*>(), this, this->GetController(), false, ECC_GameTraceChannel1);
                GameStatic->SpawnEmitterAtLocation(GetWorld(), BloodBoltParticle, OutHit.ImpactPoint);

                FVector Center = this->GetActorLocation();
                UWorld* World = GetWorld();

                DrawDebugSphere(World, OutHit.ImpactPoint, 300.0f, 16, FColor::Red, false, 0.2f);

                bIsSkillBloodBolt = false;
            }

            GameStatic->SpawnEmitterAtLocation(GetWorld(), BloodParticle, OutHit.ImpactPoint);

        }
        else
        {


            if (bIsSkillBloodBolt == true)
            {
                UGameplayStatics::ApplyRadialDamage(GetWorld(), 100.0f, OutHit.ImpactPoint, 300.0f, nullptr, TArray<AActor*>(), this, this->GetController(), false, ECC_GameTraceChannel1);
                GameStatic->SpawnEmitterAtLocation(GetWorld(), BloodBoltParticle, OutHit.ImpactPoint);

                FVector Center = this->GetActorLocation();
                UWorld* World = GetWorld();

                DrawDebugSphere(World, OutHit.ImpactPoint, 300.0f, 16, FColor::Red, false, 0.2f);

                bIsSkillBloodBolt = false;
            }


            GameStatic->SpawnEmitterAtLocation(GetWorld(), SmokeParticle, (OutHit.ImpactPoint) + (OutHit.ImpactNormal * 20));
        }
    }
}

void APlayerBase::PlayerDie()
{
    FullHealth = 0.0f;
    Health = FullHealth;
    HealthPercentage = 0.0f;
    bIsDieUi = true;
}

float APlayerBase::GetHealth()
{
    //UE_LOG(LogClass, Warning, TEXT("CheckPlayerHP"));
  

    return HealthPercentage;
}

float APlayerBase::GetMagic()
{
    return MagicPercentage;
}

FText APlayerBase::GetHealthIntText()
{
    int32 HP = FMath::RoundHalfFromZero(HealthPercentage * 100);
    FString HPS = FString::FromInt(HP);
    FString HealthHUD = HPS + FString(TEXT("%"));
    FText HPText = FText::FromString(HealthHUD);

    return HPText;

}

FText APlayerBase::GetSoulIntText()
{
    
    FString SOULS = FString::FromInt(SoulCount);
    FString SOULSHUD = SOULS + FString(TEXT("/3"));
    FText SOULText = FText::FromString(SOULSHUD);

    return SOULText;

}

FText APlayerBase::GetMagicIntText()
{
    int32 MP = FMath::RoundHalfFromZero(MagicPercentage * 100);
    FString MPS = FString::FromInt(MP);
    FString FullMPS = FString::FromInt(FullMagic);
    FString MagicHUD = MPS + FString(TEXT("/")) + FullMPS;
    FText MPText = FText::FromString(MagicHUD);

    return MPText;
}

void APlayerBase::SetDamageState()
{
    bCanBeDamaged = true;
}

void APlayerBase::DamageTimer()
{
    GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &APlayerBase::SetDamageState, 2.0f, false);
}


void APlayerBase::SetMagicValue()
{
    TimelineValue = MyTimeline->GetPlaybackPosition();
    CurveFloatValue = PreviousMagic + MagicValue * MagicCurve->GetFloatValue(TimelineValue);
    Magic = FMath::Clamp(CurveFloatValue * FullHealth, 0.0f, FullMagic);
    MagicPercentage = FMath::Clamp(CurveFloatValue, 0.0f, 1.0f);
}

void APlayerBase::SetMagicState()
{
    bCanUseMagic = true;
    MagicValue = 0.0;

}

void APlayerBase::SetMagicChange(float MagicChange)
{
    bCanUseMagic = false;
    PreviousMagic = MagicPercentage;
    MagicValue = (MagicChange / FullMagic);


    if (MyTimeline != nullptr) MyTimeline->PlayFromStart();
}

void APlayerBase::UpdateMagic()
{
    //UE_LOG(LogClass, Warning, TEXT("MagicUpdate1"));
    playerAnim->PlayReloadMontage();
    PreviousMagic = MagicPercentage;
    MagicPercentage = Magic / FullMagic;
    MagicValue = 1.0f;
    if (MyTimeline != nullptr) MyTimeline->PlayFromStart();
}

bool APlayerBase::PlayFlash()
{
    if (redFlash)
    {
        redFlash = false;
        return true;
    }

    return false;
}

bool APlayerBase::PlayYouDie()
{
    if (bIsDieUi)
    {
        bIsDieUi = false;
        return true;
    }


    return false;
}
