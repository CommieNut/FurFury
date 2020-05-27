// Fill out your copyright notice in the Description page of Project Settings.


#include "Minibomb.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Main.h"
#include "EnemyMinionAI.h"
#include "Pluton.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

//tried to learn from these video and site, but only one worked https://docs.unrealengine.com/en-US/Engine/AI/BehaviorTrees/QuickStart/5/index.html https://www.youtube.com/watch?v=3Z1A825gTA8 https://www.youtube.com/watch?v=fzgvXgHuxL4 https://www.youtube.com/watch?v=t-uiTbEUl00&list=PLWUvrI0mg8VLrvq3n2iu45lhCo69uluDK&index=2

// Sets default values
AMinibomb::AMinibomb()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	
}

// Called when the game starts or when spawned
void AMinibomb::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AMinibomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMinibomb::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
