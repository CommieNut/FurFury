// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemyappears.h"
#include "Components/BoxComponent.h"
#include "Enemy.h"

// Sets default values
AEnemyappears::AEnemyappears()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//code taught by dennis and isak
	spawnmodel = CreateDefaultSubobject<UBoxComponent>(TEXT("spawnmodel"));
	RootComponent = spawnmodel;
}

// Called when the game starts or when spawned
void AEnemyappears::BeginPlay()
{
	Super::BeginPlay();
	
	spawnblock(); //spawn enemy when game start, taught by isak and dennis.
}

// Called every frame
void AEnemyappears::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//code taught by isak and dennis.
void AEnemyappears::spawnblock() {

	FVector Position = GetActorLocation();

	UWorld* World = GetWorld();

	if (World)
	{
		for (int U{ 1 }; U < 2; U++)
		{
			for (int k{ 1 }; k < 4; k++)
			{

				Position.X = (GetActorLocation().X + U * 400);
				Position.Y = (GetActorLocation().Y + k * 500);

				AEnemy* enemy = World->SpawnActor<AEnemy>(spawn_BP, Position, FRotator::ZeroRotator);
			}
		}
	}
}

