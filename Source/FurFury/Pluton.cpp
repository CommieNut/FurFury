// Fill out your copyright notice in the Description page of Project Settings.


#include "Pluton.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
APluton::APluton()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlutonPawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PlutonPawnSensing"));

	PlutonPawnSensing->OnSeePawn.AddDynamic(this, &APluton::OnPawnSeen);
	PlutonPawnSensing->OnHearNoise.AddDynamic(this, &APluton::OnNoiseHeard);
}

// Called when the game starts or when spawned
void APluton::BeginPlay()
{
	Super::BeginPlay();
	
}

void APluton::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr) {
		return;
	}
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 0.5f);
}

void APluton::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 0.5f);
}

// Called every frame
void APluton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


