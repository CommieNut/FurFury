// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemyappears.generated.h"

UCLASS()
class FURFURY_API AEnemyappears : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyappears();
	//taught by isak and dennis.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawnmodel")
		class UBoxComponent* spawnmodel;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawnenemy")
		TSubclassOf<class AEnemy> spawn_BP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void spawnblock();
};
