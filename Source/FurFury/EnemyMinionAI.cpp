// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMinionAI.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyMinionAI::AEnemyMinionAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Hitbox = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox"));
	Hitbox->SetupAttachment(GetRootComponent());
	Hitbox->AddLocalOffset(FVector(80.f, 0.f, 0.f));



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

