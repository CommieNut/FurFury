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
	UPROPERTY(EditAnywhere, Category = "toSpawn")
		TSubclassOf<class AEnemyMinionAI> tospawn;
	UFUNCTION(BlueprintCallable)
		void spawn();
	//UFUNCTION(BlueprintCallable)
		//void spawn2();

	UPROPERTY(EditAnywhere, category = "Spawning")
		AEnemyMinionAI* getdestroyed;


	//maybe crashes when on deltatime.
	// Called when the game starts or when spawned
protected:
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "delayspawntime")
	 float spawndelaylowernumber;
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "delayspawntime")
	 float spawndelayhighernumber;
	 FTimerHandle spawntimer;


	 float spawn1to5delay;
	 float delay = 30.0f;
};
