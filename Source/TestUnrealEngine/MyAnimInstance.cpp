// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyCharacter.h"

UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animations/Greystone_Skeleton_Montage.Greystone_Skeleton_Montage'"));

	if (AM.Succeeded() == true)
	{
		attackMontage = AM.Object;
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float deltaSeconds)
{
	Super::NativeUpdateAnimation(deltaSeconds);

	APawn* pawn = TryGetPawnOwner();
	if (IsValid(pawn) == true)
	{
		speed = pawn->GetVelocity().Size();

		AMyCharacter* character = Cast<AMyCharacter>(pawn);
		if (character != nullptr)
		{
			isFalling = character->GetMovementComponent()->IsFalling();

			vertical = character->upDownValue;
			horizontal = character->leftRightValue;
		}
	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	Montage_Play(attackMontage);
}

void UMyAnimInstance::JumpToSection(int sectionIndex)
{
	FName name = GetAttackMontageName(sectionIndex);
	Montage_JumpToSection(name, attackMontage);
}

FName UMyAnimInstance::GetAttackMontageName(int sectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), sectionIndex));
}

void UMyAnimInstance::AnimNotify_AttackHit()
{
	//UE_LOG(LogTemp, Log, TEXT("AnimNotify_AttackHit"));

	onAttackHit.Broadcast();
}
