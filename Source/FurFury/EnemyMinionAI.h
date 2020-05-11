// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Main.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "EnemyMinionAI.generated.h"

class UPawnSensingComponent;

UCLASS()
class FURFURY_API AEnemyMinionAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyMinionAI();

	AMain* PlayerCharacter;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeleeAttack)
	class USphereComponent* Hitbox;

	UPROPERTY(EditAnywhere, Category = "Minion Death Function Property")
	float ftimeTilDeath = 0.225f;

	UPROPERTY(EditAnywhere, Category = "Minion Particle System")
	UParticleSystem* MinionDeathParticle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Minion Mana Drop")
	TSubclassOf<AActor> ActorToSpawn;

	//On Death Functions
	UFUNCTION(BlueprintCallable, Category = "Minion Functions")
		void deathFunction(); //EnemyToKill--;

	UFUNCTION(BlueprintCallable, Category = "Minion Functions")
		void destroyFunction();

	UFUNCTION(BlueprintCallable, Category = "Minion Functions")
		void SpawnMana(FVector Loc, FRotator Rot);
	
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
