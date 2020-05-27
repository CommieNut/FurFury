// Fill out your copyright notice in the Description page of Project Settings.
#include "Main.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyMinionAI.h"
#include "Components/SkeletalMeshComponent.h"
#include "Pickup_Stamina.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Projectile.h"
#include "TimerManager.h"

// Sets default values
AMain::AMain()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Creates the invisible sphere component we use as a hitbox to detect collision on key press. (Doesnt work yet)
	MeleeHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeHitbox"));
	MeleeHitbox->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), "R_HandSocket");

	// Create Camera Boom & Camera Boom Settings (Pulls towards the player if there's a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 1000.f; // Distance between camera and character
	CameraBoom->bUsePawnControlRotation = false; // Rotates the springarm based on controller (Disabled)
	CameraBoom->AddLocalRotation(FRotator(0.0f, -70.0f, 55.0f)); // Rotates the springarm so that its paralell to the map
	CameraBoom->bInheritPitch = false; // Disabled pitch inheritance from root component.
	CameraBoom->bInheritYaw = false; // Disabled yaw inheritance from root component.
	CameraBoom->bInheritRoll = false; // Disabled roll inheritance from root component.

	//Set size for collision capsule
	GetCapsuleComponent()->SetCapsuleSize(34.f, 88.f);

	// Create and Attach the camera to the end of the boom.
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);


	//Set our turn rates for input (DISABLED FROM CONTROLS (Mo 19.03.2020))
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	// Don't rotate when the controller rotates. (That didnt work, had to disable the keybinds to controller for the camera, aka mouse doesnt control cam anymore. -Mo 19.03.2020)
	// Let that just affect the camera
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 840.f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.5f;

	AutoPossessPlayer = EAutoReceiveInput::Player0; // Assume immediate control of character without having to set it up in project settings
	
	NoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter")); //Component that makes noice. used by AI's to detect FurFur
}

void AMain::ResetRangedCooldown()
{
	RangedCooldown = false;
}



// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMain::OnBeginOverlap); // A general overlap function. Mainly used to pick up mana. 
}



// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool Falling = GetCharacterMovement()->IsFalling();
	if (GetInputAxisValue("MoveForward") != 0 || GetInputAxisValue("MoveRight") != 0)
	{
		Moving = true;
	}else
	{
		Moving = false;
	}
	
	if (bPlayerDead != true)
	{	
		if (Moving && !Falling && states != animationStates::jumpFalling){
			states = animationStates::running;
			UE_LOG(LogTemp, Warning, TEXT("Running"));
		}else if (states == animationStates::jumpFalling && !Falling) {
			UE_LOG(LogTemp, Warning, TEXT("Landing 1"));
			states = animationStates::jumpLanding;

		}else if (states == animationStates::jumpFalling && !Falling && Moving) {
			UE_LOG(LogTemp, Warning, TEXT("Landing 2"));
			states = animationStates::jumpLanding;

		}else if (Falling) {
			UE_LOG(LogTemp, Warning, TEXT("Falling"));
			states = animationStates::jumpFalling;
		
		}else{
			UE_LOG(LogTemp, Warning, TEXT("Idling"));
			states = animationStates::idle;
		}
	}



	

	if(PlayerHealth <= 0) // Very very basic death if-statement, if the player health is less than or equal to 0, destroy this actor.
	{
		//this->Destroy();
		GetCharacterMovement()->DisableMovement();
		bPlayerDead = true;
	}
}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	// General binds.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMain::PlayerJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMain::StopJumping);
	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &AMain::MeleeAttack);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);
	PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &AMain::HealAbility); // This is a permanent ability, needs some tweaking.
	PlayerInputComponent->BindAction("Sacrifice", IE_Pressed, this, &AMain::Hurt); // This is a temporary ability used for testing. will be disabled, however converted to a cheat instead.
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMain::RangedAttack);;
}


void AMain::MoveForward(float Value) // Basic movement code for forward and backwards.
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
void AMain::MoveRight(float Value) // Basic movement code for left and right.
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);

	}
}
void AMain::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}
void AMain::LookUpAtRate(float Rate) // should be removed, not necessary as we do not really use controller input.
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
void AMain::PlayerJump()
{
	states = animationStates::jumpStart;
	Jump();
}


void AMain::MeleeAttack()
{
	if(bPlayerDead != true)
	{
		states = animationStates::attacking; //Animation state, changes to attacking on activation of this function. Does not loop.
		UE_LOG(LogTemp, Warning, TEXT("Melee Attack!"));
		TArray<AActor*> TempActors; // Make an array to contain colliding actors
		MeleeHitbox->GetOverlappingActors(TempActors, AEnemyMinionAI::StaticClass()); // Checks for colliding actors, if true then add to the temporary array. A filter is added to add enemies only.
		for (size_t i = 0; i < TempActors.Num(); i++) // runs through the array
		{
			//TempActors[i]->Destroy(); // Destroy actor in that specefic array index
			auto enemyActor = Cast<AEnemyMinionAI>(TempActors[i]);
			if(IsValid(enemyActor))
			{
				enemyActor->minionHealth -= 50;
	//			enemyActor->deathFunction();
			}
		}
	}

}
void AMain::RangedAttack()
{
	if (bPlayerDead != true && RangedCooldown == false && PlayerStamina >= 5 && projectile)
	{
		RangedCooldown = true;
		states = animationStates::fire;
		GetWorld()->GetTimerManager().SetTimer(FTFireProjectFileHandle, this, &AMain::fireProjectile, 0.700f, false);
	}
}

void AMain::fireProjectile()
{
			FVector projectileSpawnLocation = GetActorLocation() + (GetActorForwardVector() * 200.f);
			PlayerStamina -= 5;
			GetWorld()->SpawnActor<AProjectile>(projectile, projectileSpawnLocation, GetActorRotation());
			GetWorld()->GetTimerManager().SetTimer(FTCooldownTimerHandle, this, &AMain::ResetRangedCooldown, FCoolDownTime, false);
}
void AMain::HealAbility()
{
	if(PlayerHealth < 100 && PlayerStamina >= 25 && bPlayerDead != true) // Simple heal ability, if player health is less than 100 and player stamina is more than or equal to 25
	{
		PlayerHealth += 25; //add 25 health (will need tweaking)
		PlayerStamina -= 25; //remove 25 stamina (will need tweaking)
		if(PlayerHealth > 100) // If player is over 100 HP (Health points)
		{
			PlayerHealth = 100; // Set player HP back to 100. (to avoid players abusing this ability to basically have god mode)
		}
	}
}
void AMain::Hurt() // Very simple function only made for testing. (REMOVE)
{
	PlayerHealth -= 25.f;
}



void AMain::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Stamina Collide"));
	//Player collides with a potential stamina
	//Casting to check if it is a stamina actor
	APickup_Stamina* ActorCheck = Cast<APickup_Stamina>(OtherActor);
		if (IsValid(ActorCheck))
		{
			if(PlayerStamina <= 75)
			{
				PlayerStamina += 25;
				ActorCheck->Destroy();
			}
			
				//Found the actor you're looking for, time to stop
				return;
		}
		
}
