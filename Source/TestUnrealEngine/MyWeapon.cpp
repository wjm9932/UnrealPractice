// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"
#include "MyCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyWeapon::AMyWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> sw(TEXT("StaticMesh'/Game/ParagonGreystone/FX/Meshes/Heroes/Greystone/SM_Greystone_Blade_01.SM_Greystone_Blade_01'"));
	if (sw.Succeeded() == true)
	{
		weapon->SetStaticMesh(sw.Object);
	}
	weapon->SetupAttachment(RootComponent);
	trigger->SetupAttachment(weapon);

	weapon->SetCollisionProfileName(TEXT("MyCollectible"));
	trigger->SetCollisionProfileName(TEXT("MyCollectible"));
	trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));
}

// Called when the game starts or when spawned
void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AMyWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyWeapon::OnCharacterOverlap);
}

void AMyWeapon::OnCharacterOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlapped"));

	AMyCharacter* myCharacter = Cast<AMyCharacter>(otherActor);

	if (myCharacter != nullptr)
	{
		FName weaponSocket(TEXT("hand_l_socket"));

		AttachToComponent(myCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, weaponSocket);
	}
}

