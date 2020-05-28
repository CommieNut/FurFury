// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pluton.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType, Category = "Player Animation")
enum class PlutonAnimationStates : uint8 {
	headbutt,
	dswipe,
	trock,
	move,
	idle
};


UCLASS()
class FURFURY_API APluton : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APluton();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pluton CollisionSphere")
	class USphereComponent* CollisionSphere;
	
	UPROPERTY(BlueprintReadOnly, Category = "Pluton Animation")
	PlutonAnimationStates PlutonStates;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PlutonPawnSensing;

	/** True if Pluton can walk, false if not */
	bool bPlutonCanWalk = false;
	bool bPlutonCanAttack = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pluton Variables")
	int PlutonHealth = 1000;

	int RandomAttack = 0;

	float Swipes = 0;

	static constexpr int  HeadbuttC = 1;	// Static connstexpr sets the value at complation.
	static constexpr int  DoubleSwipeC = 2;
	static constexpr int  ThrowRockC = 3;

	/** Handles the delay before Pluton can walk */
	FTimerHandle PlutonWalkDelayHandle;

	void ResetWalk();

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	void Walk(APawn* SeenPawn, float DistanceToPawn, float WalkSpeed);

	void Headbutt(float DistanceToPawn);

	void DoubleSwipe(float DistanceToPawn);

	void ThrowRock(float DistanceToPawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
