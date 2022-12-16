// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "MyGameInstance.generated.h"

USTRUCT()
struct FMyCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BluePrintReadWrite)
	int32 level;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite)
	int32 attack;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite)
	int32 maxHp;
};
/**
 * 
 */
UCLASS()
class TESTUNREALENGINE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	virtual void Init() override;

	FMyCharacterData* GetStatData(int32 level);
private:
	UPROPERTY()
	class UDataTable* myStats;
};
