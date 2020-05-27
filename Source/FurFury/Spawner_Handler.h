// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner_Handler.generated.h"

UCLASS()
class FURFURY_API ASpawner_Handler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner_Handler();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Capsule")
		class USphereComponent* InvisibleShere;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSpawners") // This is used to contain all spawners instanced in the world. this runs on begin play function.
		TArray<AActor*> InWorldSpawners;	// Do not mess around with this.

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSpawners")
		TArray<AActor*> CastInWorldSpawners; // Do not mess around with this.

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawner Options")
		bool bActivateSpawnersInIndexedOrder; // Best use only in infinite spawn modes.
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawner Options")
		uint8 EnemiesToSpawnPerSpawner; //Set to 0 if you want enemies to spawn infinitely

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawner Options")
		bool bInfiniteSpawning;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay And Timing")
		bool RandDelay = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay And Timing")
		float PreSetDelayInSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay And Timing")
		float RandomDelayInSecondsMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay And Timing")
		float RandomDelayInSecondsMax;


	
	uint8 TargetSpawner;
	uint8 EnemiesKilledOnTagetSpawner;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
