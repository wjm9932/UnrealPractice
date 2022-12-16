// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DATA(TEXT("DataTable'/Game/Date/StatTable.StatTable'"));

	myStats = DATA.Object;
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance %d"), GetStatData(1)->attack);
}

FMyCharacterData* UMyGameInstance::GetStatData(int32 level)
{
	return myStats->FindRow<FMyCharacterData>(*FString::FromInt(level), TEXT(""));
}
