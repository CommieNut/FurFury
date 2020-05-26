// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner_Handler.h"
#include "Kismet/GameplayStatics.h"
#include "EnemySpawner.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"

// Sets default values
ASpawner_Handler::ASpawner_Handler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InvisibleShere = CreateDefaultSubobject<USphereComponent>(TEXT("ExistenceIndicatorSphere"));
	RootComponent = InvisibleShere;

}

// Called when the game starts or when spawned
void ASpawner_Handler::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), InWorldSpawners);

	for(int i = 0; i < InWorldSpawners.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Info (In World Spawners) = %s"), *InWorldSpawners[i]->GetName());
		auto tempSpawner = Cast<AEnemySpawner>(InWorldSpawners[i]);
		if(IsValid(tempSpawner))
		{
			CastInWorldSpawners.Add(tempSpawner);
		}
	}
}

// Called every frame
void ASpawner_Handler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

