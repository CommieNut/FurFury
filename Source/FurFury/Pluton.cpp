// Fill out your copyright notice in the Description page of Project Settings.


#include "Pluton.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Main.h"
#include "Kismet/GameplayStatics.h"

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
	// CALCULATE DISTANCE
	float XDistance = 0;
	float YDistance = 0;
	float XYDistance = 0;

	//calculates a positive XDistance.
	if (GetActorLocation().X > SeenPawn->GetActorLocation().X) {
		XDistance = GetActorLocation().X - SeenPawn->GetActorLocation().X;
	}
	else {
		XDistance = SeenPawn->GetActorLocation().X - GetActorLocation().X;
	}
	//calculates a positive YDistance.
	if (GetActorLocation().Y > SeenPawn->GetActorLocation().Y) {
		YDistance = GetActorLocation().Y - SeenPawn->GetActorLocation().Y;
	}
	else {
		YDistance = SeenPawn->GetActorLocation().Y - GetActorLocation().Y;
	}
	XYDistance = sqrt(pow(XDistance, 2) + pow(YDistance, 2)); //Pythagoras theorem, to calculate distance between player and minion (XYDistance)

	//Randomly decides Pluton attack.
	if (RandomNumber == 0 && bPlutonCanAttack == true){
		RandomNumber = rand() % 2 + 1;
		UE_LOG(LogTemp, Warning, TEXT("Attack: %f"), RandomNumber);
	}

	if (RandomNumber == 1) { // Charged Headbutt
		if (bPlutonCanWalk) {
			GetWorldTimerManager().ClearTimer(PlutonWalkDelayHandle);
			Walk(SeenPawn, XYDistance, 20);
			Headbutt(XYDistance);
		}
		else if (!GetWorldTimerManager().IsTimerActive(PlutonWalkDelayHandle)) {
			GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 1.0f, false);
		}
	}
	else if(RandomNumber == 2) //Double Swipe
	{ 
		if (bPlutonCanWalk) {
			GetWorldTimerManager().ClearTimer(PlutonWalkDelayHandle);
			Walk(SeenPawn, XYDistance, 12);
			DoubleSwipe(XYDistance);
		}

		else if (!GetWorldTimerManager().IsTimerActive(PlutonWalkDelayHandle)) {
			GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 0.3f, false);
		}
	}
	else if (RandomNumber == 3) { //Throw Rock

	}
	else if (RandomNumber == 4) { 

	}
	else if (RandomNumber == 5){

	}
}

void APluton::ResetWalk()
{
	bPlutonCanAttack = true;
	bPlutonCanWalk = true;
	UE_LOG(LogTemp, Warning, TEXT("Walk = true"));
}

void APluton::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 0.5f);

	FVector Direction = NoiseInstigator->GetActorLocation() - GetActorLocation(); //Gets the location of the SEEN pawn, and calculates the direction to the pawn.
	Direction.Normalize();
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f; //Resets Pitch and Roll. The enemy is now unable to rotate in these directions.
	NewLookAt.Roll = 0.0f;
	SetActorRotation(NewLookAt); // rotates the enemy towards the player.
}

void APluton::Walk(APawn* SeenPawn, float XYDistance, float WalkSpeed) 
{

		DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 0.5f);

		FVector Direction = SeenPawn->GetActorLocation() - GetActorLocation(); //Gets the location of the SEEN pawn, and calculates the direction to the pawn.
		Direction.Normalize();
		FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
		NewLookAt.Pitch = 0.0f; //Resets Pitch and Roll. The enemy is now unable to rotate in these directions.
		NewLookAt.Roll = 0.0f;
		SetActorRotation(NewLookAt); // rotates the enemy towards the player.

		if (XYDistance >= 300) {
			AddActorLocalOffset(FVector(WalkSpeed, 0.f, 0.f)); //Moves the character in Plutons X-direction.
		}
		else {
			bPlutonCanWalk = false;
		}
}

void APluton::Headbutt(float DistanceToPawn)
{
	if (DistanceToPawn <= 300) {
		/*CHANGE ANIMATION

		ENABLE ANIM;
		Set timer to turn anim off?

		*/

		AMain* Player = Cast<AMain>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (IsValid(Player))
		{
			UE_LOG(LogTemp, Warning, TEXT("Headbutt Hit"));
			Player->PlayerHealth -= 25.0f;
		}
		RandomNumber = 0;
		GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 3.0f, false);
	}
}

void APluton::DoubleSwipe(float DistanceToPawn)
{
	if(Swipes >= 2){
		RandomNumber = 0;
		Swipes = 0;
		bPlutonCanWalk = false;
		GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 3.0f, false);
	}
	else if (DistanceToPawn <= 300 && bPlutonCanAttack == true) {
		Swipes++;
		UE_LOG(LogTemp, Warning, TEXT("Double Swipe"));
		/*CHANGE ANIMATION
		 
		ENABLE ANIM;
		Set timer to turn anim off?

		*/
		AMain* Player = Cast<AMain>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (IsValid(Player))
		{
			Player->PlayerHealth -= 25.0f;
		}
		bPlutonCanAttack = false;
		GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 0.5f, false);
	}
}

// Called every frame
void APluton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


