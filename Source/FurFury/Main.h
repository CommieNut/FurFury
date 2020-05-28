// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"

class UPawnNoiseEmitterComponent;

UENUM(BlueprintType, Category = "Player Animation")
enum class animationStates : uint8 {
	idle,
	attacking,
	running,
	jumpStart,
	jumpFalling,
	jumpLanding,
	jumpGliding, // Not currently in use.
	fire,
	dead
};

UCLASS()
class FURFURY_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MeleeAttack)
	class UCapsuleComponent * MeleeHitbox;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Variables")
	int EnemyKilled = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Variables")
	int EnemySpawned = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Variables")
	int PlayerHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Variables")
	int PlayerStamina = 100;

	UPROPERTY(EditAnywhere, Category = "keys")
	int KeysCollected = 0;

	UPROPERTY(EditAnywhere, Category = "keys")
	int KeysToCollect = 3;

	UPROPERTY(BlueprintReadOnly, Category = "Player Animation")
	animationStates states;

	UPROPERTY(EditAnywhere, Category = "Player Ranged Attack Properties")
	TSubclassOf<class AProjectile> projectile;

	FTimerHandle FTCooldownTimerHandle;
	bool RangedCooldown = false;

	UPROPERTY(EditAnywhere, Category = "Player Ranged Attack Properties")
	float FCoolDownTime = 0.5f;

	UFUNCTION(BlueprintCallable, Category= "Player Ranged Attack Properties")
	void ResetRangedCooldown();

	UPROPERTY(BlueprintReadWrite, Category = "Player Variables")
	bool bPlayerDead;

	bool SetOnce = false;

	UPROPERTY(EditAnywhere, Category = "Audio Components")
		class UAudioComponent* JumpAudio;

	UPROPERTY(EditAnywhere, Category = "Audio Components")
		class UAudioComponent* FootstepsAudio;

	UPROPERTY(EditAnywhere, Category = "Audio Components")
		class UAudioComponent* HitCommentAudio;

	UPROPERTY(EditAnywhere, Category = "Audio Components")
		class UAudioComponent* RangedAttackAudio;

	UPROPERTY(EditAnywhere, Category = "Audio Components")
		class UAudioComponent* MeleeSwingAudio;

	FTimerHandle FTFireProjectFileHandle;
	void fireProjectile();
	bool Moving;
	bool bCanOpenDoor = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	UPawnNoiseEmitterComponent* NoiseEmitterComp;

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

	void PlayerJump();
	
	void MeleeAttack();

	void HealAbility();
	void Hurt();

	void RangedAttack();


	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};  

