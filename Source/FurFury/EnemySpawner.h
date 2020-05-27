// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class FURFURY_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		class UBoxComponent* spawnbox;
	
	UPROPERTY(EditAnywhere, Category = "Actors To Spawn")
		TSubclassOf<class AEnemyMinionAI> ActorToSpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnerIdentifiers")
		int SpawnerIndex = 0; //Utilized by developers to order the spawners in the desired order. (Important for the spawner handler)

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SpawnerManipulators")
		bool spawnerActive = false;
	
	UPROPERTY(EditAnywhere, category = "Spawning")
		AEnemyMinionAI* getdestroyed;

	UFUNCTION(BlueprintCallable)
		void spawn();


	float LocalPreSetDelayInSeconds;
	float LocalRandomDelayInSecondsMin;
	float LocalRandomDelayInSecondsMax;
	FTimerHandle SpawnTimer;


	//maybe crashes when on deltatime.
	// Called when the game starts or when spawned
protected:
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	 float Final;
};
