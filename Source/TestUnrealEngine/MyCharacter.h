// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class TESTUNREALENGINE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	void UpDown(float value);
	void LeftRight(float value);
	void Yaw(float value);
	void Attack();
	void CheckAttack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted);

private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* camera;

	UPROPERTY(VisibleAnywhere, Category = Pawn)
	bool isAttacking = false;

	UPROPERTY(VisibleAnywhere)
	class UMyAnimInstance* myInstance;

	UPROPERTY()
	int attackIndex = 0;

public:
	UPROPERTY()
	float upDownValue = 0.f;

	UPROPERTY()
	float leftRightValue = 0.f;


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* weapon;

	UPROPERTY(VisibleAnywhere)
	class UMyStatComponent* stat;
};
