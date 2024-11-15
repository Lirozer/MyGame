// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyDrink.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnergyDrink::AEnergyDrink()
{
	DrinkStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DrinkStaticMesh"));
	DrinkStaticMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	DrinkStaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AEnergyDrink::Overlap);

	ConstructorHelpers::FObjectFinder<USoundBase> Sound(TEXT("/Game/Spawners/DrinkSound"));

	DrinkSound = Sound.Object;

}

void AEnergyDrink::Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& HitResult)
{
	IInteractInterface::Execute_AddStamina(OtherActor, AddStamina);

	UGameplayStatics::PlaySoundAtLocation(this, DrinkSound, GetActorLocation());

	Destroy();


}


