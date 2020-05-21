// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pluton.generated.h"

class UPawnSensingComponent;

UCLASS()
class FURFURY_API APluton : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APluton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PlutonPawnSensing;

	/** True if Pluton can walk, false if not */
	bool bPlutonCanWalk = false;

	bool bTEST = true;

	/** Handles the delay before Pluton can walk */
	FTimerHandle PlutonWalkDelayHandle;

	void ResetWalk();

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	void Walk(APawn* SeenPawn, float DistanceToPawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
