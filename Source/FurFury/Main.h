// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"

UCLASS()
class FURFURY_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeleeAttack)
	class USphereComponent* MeleeHitbox;

	/** Camera Boom positioning the camera behind the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Base turn rates to scale turning functions for the camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Variables")
	int EnemyToKill = 50;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Variables")
	int EnemySpawned = 50;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Variables")
	float PlayerHealth = 1.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Variables")
	float PlayerStamina = 1.0;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forwards/Backwards input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called via input to turn at a given rate
	* @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/** Called via input to look up/down at a given rate
	* @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired look up/down rate
	*/
	void LookUpAtRate(float Rate);

	void MeleeAttack();


	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};  
