// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Main.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "EnemyMinionAI.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType, Category = "Player Animation")
enum class MinionAnimationStates : uint8 {
	idle,
	running,
	dead
};

UCLASS()
class FURFURY_API AEnemyMinionAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyMinionAI();
	
	AMain* PlayerCharacter;

	UPROPERTY(EditAnywhere, Category = "Minion Death Function Property")
	float ftimeTilDeath = 0.600f/*0.225f*/;

	UPROPERTY(EditAnywhere, Category = "Minion Particle System")
	UParticleSystem* MinionDeathParticle;

	UPROPERTY(EditAnywhere, Category = "Minion Particle System")
	UParticleSystem* MinionDamagedParticle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Minion Mana Drop")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "Minion Health")
	int minionHealth = 100;

	//On Death Functions
	UFUNCTION(BlueprintCallable, Category = "Minion Functions")
		void deathFunction();

	UFUNCTION(BlueprintCallable, Category = "Minion Functions")
		void destroyFunction();

	UFUNCTION(BlueprintCallable, Category = "Minion Functions")
		void SpawnMana(FVector Loc, FRotator Rot);

	UPROPERTY(BlueprintReadOnly, Category = "Minion Animation")
		MinionAnimationStates MinionStates;


	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Minion Damage Output")
		float DamageCoolDown = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Minion Damage Output")
		int DamagePerHit = 0;

	bool bCanDamage = true;

	FTimerHandle CanDamageTimerReset;

	void CanDamageResetFunction();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensing;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
