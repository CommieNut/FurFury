// Fill out your copyright notice in the Description page of Project Settings.


#include "Pluton.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Engine/World.h"

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

void APluton::ResetWalk()
{
	bPlutonCanWalk = true;
	UE_LOG(LogTemp, Warning, TEXT("Walk = true"));
}

void APluton::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr) {
		return;
	}
	if (!GetWorldTimerManager().IsTimerActive(PlutonWalkDelayHandle)){
		DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 0.5f);

		FVector Direction = SeenPawn->GetActorLocation() - GetActorLocation(); //Gets the location of the SEEN pawn, and calculates the direction to the pawn.
		Direction.Normalize();
		FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
		NewLookAt.Pitch = 0.0f; //Resets Pitch and Roll. The enemy is now unable to rotate in these directions.
		NewLookAt.Roll = 0.0f;
		SetActorRotation(NewLookAt); // rotates the enemy towards the player.
	}
	// CALCULATE DISTANCE
	float XDistance = 0;
	float YDistance = 0;
	float XYDistance = 0;
	
	//calculates a positive XDistance.
	if (GetActorLocation().X > SeenPawn->GetActorLocation().X) {
		XDistance = GetActorLocation().X - SeenPawn->GetActorLocation().X;
	}else {
		XDistance = SeenPawn->GetActorLocation().X - GetActorLocation().X;
	}
	//calculates a positive YDistance.
	if (GetActorLocation().Y > SeenPawn->GetActorLocation().Y) {
		YDistance = GetActorLocation().Y - SeenPawn->GetActorLocation().Y;
	}else {
		YDistance = SeenPawn->GetActorLocation().Y - GetActorLocation().Y;
	}
	XYDistance = sqrt(pow(XDistance, 2) + pow(YDistance, 2)); //Pythagoras theorem, to calculate distance between player and minion (XYDistance)
															  
	// WALK
	if (bPlutonCanWalk) {
		GetWorldTimerManager().ClearTimer(PlutonWalkDelayHandle);
		Walk(SeenPawn, XYDistance);
	}
	else if(!GetWorldTimerManager().IsTimerActive(PlutonWalkDelayHandle)){
		GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 1.3f, false);
	}
	
}

void APluton::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 0.5f);
}

void APluton::Walk(APawn* SeenPawn, float XYDistance) {
	UE_LOG(LogTemp, Warning, TEXT("Distance: %f,"), XYDistance);
	if (XYDistance >= 300) {
		AddActorLocalOffset(FVector(20.f, 0.f, 0.f)); //Moves the character in Plutons X-direction.
	}
	else {
		
		bPlutonCanWalk = false;
	}
}

// Called every frame
void APluton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


