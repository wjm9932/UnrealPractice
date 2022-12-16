// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<ACharacter> BP_Character(TEXT("Blueprint'/Game/Blueprints/BP_MyCharacter.BP_MyCharacter_C'"));

	if (BP_Character.Succeeded() == true)
	{
		DefaultPawnClass = BP_Character.Class;
	}
}