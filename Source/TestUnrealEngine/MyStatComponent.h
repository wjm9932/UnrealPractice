// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTUNREALENGINE_API UMyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	void SetLevel(int32 level);
	void OnAttack(float DamageAmount);

	int32 GetLevel() { return comLevel; }
	int32 GetHp() { return comHp; }
	int32 GetAttack() { return comAttack; }

private:
	UPROPERTY(EditAnyWhere, Category=Stat, Meta=(AllowPrivateAccess = true))
	int32 comLevel;

	UPROPERTY(EditAnyWhere, Category=Stat, Meta=(AllowPrivateAccess = true))
	int32 comHp;

	UPROPERTY(EditAnyWhere, Category=Stat, Meta=(AllowPrivateAccess = true))
	int32 comAttack;
		
};
