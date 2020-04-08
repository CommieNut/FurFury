// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Main.h"
#include "GameFramework/Character.h"
#include "EnemyMinionAI.generated.h"

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


	//On Death Functions
	UFUNCTION(BlueprintCallable, Category = "Minion Functions")
	void deathFunction(); //EnemyToKill--;

	UFUNCTION(BlueprintCallable, Category = "Minion Functions")
	void destroyFunction();

	UPROPERTY(EditAnywhere, Category = "Minion Death Function Property")
	float ftimeTilDeath = 0.225f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
