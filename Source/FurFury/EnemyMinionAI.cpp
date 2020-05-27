// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMinionAI.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Main.h"
#include "AIController.h"


// Sets default values
AEnemyMinionAI::AEnemyMinionAI()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Hitbox = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox"));
	Hitbox->SetupAttachment(GetRootComponent());
	Hitbox->AddLocalOffset(FVector(80.f, 0.f, 0.f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Gruntling/Bomber/P_FireBombExplosion.P_FireBombExplosion'"));
	MinionDeathParticle = Particle.Object;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));

	PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyMinionAI::OnPawnSeen);
	PawnSensing->OnHearNoise.AddDynamic(this, &AEnemyMinionAI::OnNoiseHeard);
}
void AEnemyMinionAI::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		MinionStates = MinionAnimationStates::idle;
		return;
	}
		// visual test for debugging (Draws a red sphere if the enemy can see FurFur).
		// DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 0.5f);

		FVector Direction = SeenPawn->GetActorLocation() - GetActorLocation(); //Gets the location of the SEEN pawn, and calculates the direction to the pawn.
		Direction.Normalize();
		FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
		NewLookAt.Pitch = 0.0f; //Resets Pitch and Roll. The enemy is now unable to rotate in these directions.
		NewLookAt.Roll = 0.0f;
		SetActorRotation(NewLookAt); // rotates the enemy towards the player.
		AddActorLocalOffset(FVector(15.f, 0.f, 0.f)); //Moves the enemy forwards, (towards player).
		MinionStates = MinionAnimationStates::running;

	
	

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

		AMain* Player = Cast<AMain>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (IsValid(Player) && XYDistance <= 100)
		{
			Player->PlayerHealth -= 1;
		}
		else {
			MinionStates = MinionAnimationStates::idle;
			return;
		}

}

void AEnemyMinionAI::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	// visual test for debugging (Draws a green sphere if the enemy can hear FurFur).
	// DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 0.5f);

	FVector Direction = Location - GetActorLocation(); //Gets the location of the SEEN pawn, and calculates the direction to the pawn.
	Direction.Normalize();


	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f; //Resets Pitch and Roll. The enemy is now unable to rotate in these directions.
	NewLookAt.Roll = 0.0f;
	SetActorRotation(NewLookAt); // rotates the enemy towards the player.

	AMain* Player = Cast<AMain>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->PlayerHealth -= 0.5;
	}
}

void AEnemyMinionAI::deathFunction()
{
	GetCharacterMovement()->DisableMovement();
	MinionStates = MinionAnimationStates::dead;
	FTimerHandle THandle;
	GetWorld()->GetTimerManager().SetTimer(THandle, this, &AEnemyMinionAI::destroyFunction, ftimeTilDeath, false);
}

void AEnemyMinionAI::destroyFunction()
{
	if (minionHealth <= 0)
	{
		auto Player = Cast<AMain>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (IsValid(Player))
		{
			Player->EnemyKilled++;
		}
		UE_LOG(LogTemp, Warning, TEXT("Enemy Destroyed!"));
		if (MinionDeathParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MinionDeathParticle, GetActorLocation(), GetActorRotation(), true, EPSCPoolMethod::None, true);
		}
		this->SpawnMana(GetActorLocation(), GetActorRotation());
		this->Destroy();
	}
	else // if enemy is not dead, spawn "hit" particle
	{    //Spawns MinionDamagedParticle
		if (MinionDamagedParticle) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MinionDamagedParticle, GetActorLocation(), GetActorRotation(), true, EPSCPoolMethod::None, true);
		}
	}
}

void AEnemyMinionAI::SpawnMana(FVector Loc, FRotator Rot)
{
	FActorSpawnParameters SpawnParam;
	AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn, Loc, Rot, SpawnParam);
	UE_LOG(LogTemp, Warning, TEXT("Stamina Spawned"));
}

// Called when the game starts or when spawned
void AEnemyMinionAI::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyMinionAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float Velocity = GetVelocity().Size();

	if (minionHealth <= 0) {
		deathFunction();
	}
}

// Called to bind functionality to input
void AEnemyMinionAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


