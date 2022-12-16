// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	bWantsInitializeComponent = true;

	comLevel = 1;
}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	SetLevel(comLevel);
}

void UMyStatComponent::SetLevel(int32 newLevel)
{
	auto myGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (myGameInstance)
	{
		auto statData = myGameInstance->GetStatData(newLevel);
		
		if (statData)
		{
			comLevel = statData->level;
			comHp = statData->maxHp;
			comAttack = statData->attack;
		}
	}
}

void UMyStatComponent::OnAttack(float DamageAmount)
{
	comHp -= DamageAmount;
	if (comHp < 0)
	{
		comHp = 0;
	}

	UE_LOG(LogTemp, Warning, TEXT("OnAttacked %d"), comHp);
}

