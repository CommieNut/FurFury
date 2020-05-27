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
#include "Perception/PawnSensingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Minibombcontroller.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Public/TimerManager.h"
#include "Kismet/kismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"

//tried to learn from these video and site, but only one worked https://docs.unrealengine.com/en-US/Engine/AI/BehaviorTrees/QuickStart/5/index.html https://www.youtube.com/watch?v=3Z1A825gTA8 https://www.youtube.com/watch?v=fzgvXgHuxL4 https://www.youtube.com/watch?v=t-uiTbEUl00&list=PLWUvrI0mg8VLrvq3n2iu45lhCo69uluDK&index=2

// Sets default values
AMinibomb::AMinibomb()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	objectmodels = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Objectmodel"));
	
	appeartimerdelaylower = 0.1f;
	appeartimedelaybigger = 0.5f;

}

FVector AMinibomb::getrandomplace() {
	FVector firstarea = objectmodels->Bounds.Origin;
	FVector extending = objectmodels->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(firstarea, extending);

}

// Called when the game starts or when spawned
void AMinibomb::BeginPlay()
{
	Super::BeginPlay();

	timethirdfactor = FMath::FRandRange(appeartimerdelaylower, appeartimedelaybigger);
	GetWorldTimerManager().SetTimer(appeartimer, this, &AMinibomb::spawnitem, timethirdfactor, false);

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

void AMinibomb::spawnitem() {
	if (appear != NULL) {
		UWorld* world = GetWorld();
		if (world) {
			FActorSpawnParameters objectplace;
			objectplace.Owner = this;
			objectplace.Instigator = Instigator;

			FVector callforrandom = getrandomplace();

			FRotator angling;
			angling.Yaw = FMath::FRand() * 360.0f;
			angling.Pitch = FMath::FRand() * 360.0f;
			angling.Roll = FMath::FRand() * 360.0f;

			AProjectile* appearfactor = world->SpawnActor<AProjectile>(appear, callforrandom, angling, objectplace);
			GetWorldTimerManager().SetTimer(appeartimer, this, &AMinibomb::spawnitem, timethirdfactor, false);


		}
	}
}