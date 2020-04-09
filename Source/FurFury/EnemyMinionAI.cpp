// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMinionAI.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"

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


}

void AEnemyMinionAI::deathFunction()
{
	FTimerHandle THandle;
	GetWorld()->GetTimerManager().SetTimer(THandle, this, &AEnemyMinionAI::destroyFunction, ftimeTilDeath, false);
}

void AEnemyMinionAI::destroyFunction()
{
	auto Player = Cast<AMain>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if(IsValid(Player))
	{
		Player->EnemyToKill--;
	}
	UE_LOG(LogTemp, Warning, TEXT("Enemy Destroyed!"));
	if(MinionDeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MinionDeathParticle, GetActorLocation(), GetActorRotation(), true, EPSCPoolMethod::None, true);
	}
	this->Destroy();
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

}

// Called to bind functionality to input
void AEnemyMinionAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

