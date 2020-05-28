// Fill out your copyright notice in the Description page of Project Settings.


#include "Pluton.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Main.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APluton::APluton()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlutonPawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PlutonPawnSensing"));

/*
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox"));
	CollisionSphere->SetupAttachment(GetRootComponent());
	CollisionSphere->AddLocalOffset(FVector(0.f, 0.f, 0.f));
	CollisionSphere->SetRelativeScale3D(FVector(7.f, 7.f, 7.f));
	CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
*/
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
		PlutonStates = PlutonAnimationStates::idle;
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
	if (RandomAttack == 0 && bPlutonCanAttack == true){
		RandomAttack = FMath::RandRange(1, 3);
		UE_LOG(LogTemp, Warning, TEXT("Attack: %d"), RandomAttack);
	}

	switch (RandomAttack) {

	case HeadbuttC: // 1
		if (bPlutonCanWalk) {
			GetWorldTimerManager().ClearTimer(PlutonWalkDelayHandle);
			Walk(SeenPawn, XYDistance, 20);
			Headbutt(XYDistance);
		}
		else if (!GetWorldTimerManager().IsTimerActive(PlutonWalkDelayHandle)) {
			GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 1.5f, false);
		}
		break;

	case DoubleSwipeC: // 2
		if (bPlutonCanWalk) {
			GetWorldTimerManager().ClearTimer(PlutonWalkDelayHandle);
			Walk(SeenPawn, XYDistance, 12);
			DoubleSwipe(XYDistance);
		}
		else if (!GetWorldTimerManager().IsTimerActive(PlutonWalkDelayHandle)) {
			GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 0.3f, false);
		}
		break;

	case ThrowRockC: // 3
		if (bPlutonCanWalk) {
			GetWorldTimerManager().ClearTimer(PlutonWalkDelayHandle);
			Walk(SeenPawn, XYDistance, 0);
			ThrowRock(XYDistance);
		}
		else if (!GetWorldTimerManager().IsTimerActive(PlutonWalkDelayHandle)) {
			GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 1.5f, false);
		}
		break;
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
		
		if (XYDistance >= 300 && RandomAttack != ThrowRockC) {
			PlutonStates = PlutonAnimationStates::move;
			AddActorLocalOffset(FVector(WalkSpeed, 0.f, 0.f)); //Moves the character in Plutons X-direction.
		}
		else {
			bPlutonCanWalk = false;
			PlutonStates = PlutonAnimationStates::idle;
		}
}

void APluton::Headbutt(float DistanceToPawn)
{
	if (DistanceToPawn <= 300) {
		PlutonStates = PlutonAnimationStates::headbutt;

		AMain* Player = Cast<AMain>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (IsValid(Player))
		{
			UE_LOG(LogTemp, Warning, TEXT("Headbutt Hit"));
			Player->PlayerHealth -= 20;
		}
		RandomAttack = 0;
		GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 2.0f, false);
	}
}

void APluton::DoubleSwipe(float DistanceToPawn)
{
	if(Swipes >= 2){
		RandomAttack = 0;
		Swipes = 0;
		bPlutonCanWalk = false;
		GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 2.0f, false);
	}
	else if (DistanceToPawn <= 300 && bPlutonCanAttack == true) {
		Swipes++;
		UE_LOG(LogTemp, Warning, TEXT("Double Swipe"));
		PlutonStates = PlutonAnimationStates::dswipe;
		AMain* Player = Cast<AMain>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (IsValid(Player))
		{
			Player->PlayerHealth -= 15;
		}
		bPlutonCanAttack = false;
		GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 0.5f, false);
	}
}

void APluton::ThrowRock(float DistanceToPawn)
{
	PlutonStates = PlutonAnimationStates::trock;
	FVector projectileSpawnLocation = GetActorLocation() + (GetActorForwardVector() * 200.f);
	//GetWorld()->SpawnActor<AProjectile>(projectile, projectileSpawnLocation, GetActorRotation());
	//GetWorld()->GetTimerManager().SetTimer(FTCooldownTimerHandle, this, &AMain::ResetRangedCooldown, FCoolDownTime, false);

	/*CHANGE ANIMATION

		States = animationStates::ThrowRock; ?

	*/

	AMain* Player = Cast<AMain>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (IsValid(Player))
	{
		UE_LOG(LogTemp, Warning, TEXT("Rock throw hit."));
		Player->PlayerHealth -= 20;
	}
	RandomAttack = 0;
	GetWorld()->GetTimerManager().SetTimer(PlutonWalkDelayHandle, this, &APluton::ResetWalk, 2.0f, false);
}

// Called every frame
void APluton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if(!bPlutonCanWalk)
	{
		PlutonStates = PlutonAnimationStates::idle;
	}
}


