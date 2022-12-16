// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "MyWeapon.h"
#include "MyStatComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	springArm->SetupAttachment(GetRootComponent());
	camera->SetupAttachment(springArm);

	springArm->TargetArmLength = 500.f;
	springArm->SetRelativeRotation(FRotator(-35.f,0.f,0.f));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> staticMesh(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (staticMesh.Succeeded() == true)
	{
		GetMesh()->SetSkeletalMesh(staticMesh.Object);
	}

	stat = CreateDefaultSubobject<UMyStatComponent>(TEXT("STAT"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//FName weaponSocket(TEXT("hand_l_socket"));

	//AMyWeapon* dropWeapon = GetWorld()->SpawnActor<AMyWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);

	//if (dropWeapon != nullptr)
	//{
	//	//dropWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, weaponSocket);
	//}
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	myInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	if (myInstance != nullptr)
	{
		myInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);
		myInstance->onAttackHit.AddUObject(this, &AMyCharacter::CheckAttack);
	}	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyCharacter::Yaw);
}

void AMyCharacter::UpDown(float val)
{
	upDownValue = val;
	AddMovementInput(GetActorForwardVector(), val);
}

void AMyCharacter::LeftRight(float val)
{
	leftRightValue = val;
	AddMovementInput(GetActorRightVector(), val);
}

void AMyCharacter::Yaw(float value)
{
	AddControllerYawInput(value);
}

void AMyCharacter::Attack()
{
	if (isAttacking == false)
	{
		myInstance->PlayAttackMontage();
		myInstance->JumpToSection(attackIndex);
		attackIndex = (attackIndex + 1) % 3;
		isAttacking = true;
	}
}

void AMyCharacter::CheckAttack()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 100.f;
	float attackRadius = 50.f;

	bool result = GetWorld()->SweepSingleByChannel(OUT hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(attackRadius), params);

	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;
	float halfHeight = attackRange * 0.5f + attackRadius;
	FQuat rotation = FRotationMatrix::MakeFromZ(vec).ToQuat();
	FColor drawColor;

	if (result == true)
	{
		drawColor = FColor::Red;
	}

	DrawDebugCapsule(GetWorld(), center, halfHeight, attackRadius, rotation, drawColor, false, 2.f);

	if (result == true && hitResult.Actor.IsValid() == true)
	{
		UE_LOG(LogTemp, Log, TEXT("Hit Actor : % s"), *hitResult.Actor->GetName());

		FDamageEvent damageEvent;
		hitResult.Actor->TakeDamage(stat->GetAttack(), damageEvent, GetController(), this);
	}
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted)
{
	isAttacking = false;
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	stat->OnAttack(DamageAmount);

	return DamageAmount;
}