// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyTraining.h"
#include "Components/WidgetComponent.h"
#include "MonsterWidget.h"

// Sets default values
ADummyTraining::ADummyTraining()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyTrainingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DummyTraining"));

	HPBarWidget = CreateAbstractDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));

	HPBarWidget->SetupAttachment(DummyTrainingMesh);

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/AI/Monster/BP_MonsterUI.BP_MonsterUI_C"));

	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.f, 50.0f));

	}
}

// Called when the game starts or when spawned
void ADummyTraining::BeginPlay()
{
	Super::BeginPlay();

	FullHealth = 200.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;

	// Dummy 도 몬스터와 같은 채력 Ui 를 쓴다
	auto CharacterWidget = Cast<UMonsterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget)
	{
		//UE_LOG(LogClass, Warning, TEXT("CheckMonsterHP1"));
		CharacterWidget->BindStaticMesh(this);
	}
	
}

// Called every frame
void ADummyTraining::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ADummyTraining::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//UE_LOG(LogClass, Warning, TEXT("GetDamage"));

	GetWorldTimerManager().ClearTimer(HealthTimerHandle);
	UpdateHealth(-DamageAmount);
	GetWorldTimerManager().SetTimer(HealthTimerHandle, this, &ADummyTraining::UpdateHealthTimer, 4.0f, false);


	return 0.0f;
}

void ADummyTraining::UpdateHealth(float HealthChange)
{

	Health = FMath::Clamp(Health += HealthChange, 0.0f, FullHealth);
	HealthPercentage = Health / FullHealth;
	OnHPChanged.Broadcast();



	//UE_LOG(LogClass, Warning, TEXT("CheckMonsterHP"));
}

void ADummyTraining::UpdateHealthTimer()
{

	Health = 200.f;
	HealthPercentage = Health / FullHealth;
	OnHPChanged.Broadcast();



	//UE_LOG(LogClass, Warning, TEXT("CheckMonsterHP"));
}

float ADummyTraining::GetHealth()
{
	//UE_LOG(LogClass, Warning, TEXT("CheckMonsterHP"));
	return HealthPercentage;
}