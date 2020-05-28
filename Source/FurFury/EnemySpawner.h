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

	UPROPERTY(VisibleAnywhere)
	USceneComponent* MainRootComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawn")
		class UBoxComponent* spawnbox;
	
	UPROPERTY(EditAnywhere, Category = "Spawner Settings")
		TSubclassOf<class ACharacter> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawner Settings")
		bool bInfiniteSpawns = false;

	UPROPERTY(EditAnywhere, Category = "Spawner Settings")
		bool RandomTimerMinMax = true;

	UPROPERTY(EditAnywhere, Category = "Spawner Settings")
		bool SpawnLocationRandomWithinBoxLimits = false;

	UPROPERTY(EditAnywhere, Category = "Spawner Settings")
		int AmountOfActors = 10; //MIN 1!!!
	
	UPROPERTY(EditAnywhere, Category = "Spawner Settings")
		float LocalPreSetDelayInSeconds = 10.f;

	UPROPERTY(EditAnywhere, Category = "Spawner Settings")
		float LocalRandomDelayInSecondsMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "Spawner Settings")
		float LocalRandomDelayInSecondsMax = 10.f;


	FVector spawnlocation;
	FVector scale;
	FTimerHandle SpawnTimer;
	float Final;
	bool ReadyToSpawn = true;
	void spawn();


	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnerIdentifiers") "SCRAPPED"
	//	int SpawnerIndex = 0; //Utilized by developers to order the spawners in the desired order. (Important for the spawner handler) "SCRAPPED"

	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SpawnerManipulators")
	//	bool spawnerActive = false;
	
	//UPROPERTY(EditAnywhere, category = "Spawning")
	//	AEnemyMinionAI* getdestroyed;





	//maybe crashes when on deltatime.
	// Called when the game starts or when spawned
protected:
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


;
};
