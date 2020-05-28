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
#include "objectspawn.h"
#include "Objectitempickable.h"
#include "Engine/Engine.h"
#include "UObject/ObjectMacros.h"
#include "Materials/MaterialInstance.h"


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
	GetCharacterMovement()->AirControl = 0.4f;

	AutoPossessPlayer = EAutoReceiveInput::Player0; // Assume immediate control of character without having to set it up in project settings
	
	NoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter")); //Component that makes noice. used by AI's to detect FurFur


		// objectpickup start

	objectpickrange = CreateDefaultSubobject<USphereComponent>(TEXT("objectpickrange"));
	objectpickrange->AttachTo(RootComponent);
	objectpickrange->SetSphereRadius(200.f);

	currentpower = 1.f;
	playercurrentpower = currentpower;

	//objectpickup end

	// change color on power, didn¨t work.
	//speedfactor = 0.75f;
	//basespeed = 10.0f;
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
	if (bPlayerDead != true)
	{
		if (GetInputAxisValue("MoveForward") != 0 || GetInputAxisValue("MoveRight") != 0) {
			states = animationStates::running;
		}else{
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMain::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMain::StopJumping);
	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &AMain::MeleeAttack);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);
	PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &AMain::HealAbility); // This is a permanent ability, needs some tweaking.
	PlayerInputComponent->BindAction("Sacrifice", IE_Pressed, this, &AMain::Hurt); // This is a temporary ability used for testing. will be disabled, however converted to a cheat instead.
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMain::RangedAttack);;
	PlayerInputComponent->BindAction("objectpickup", IE_Pressed, this, &AMain::objectpickup); //objectpickup code using H as input keyboard
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
	//			enemyActor->deathFunction();/
			}
		}	
	}

}
void AMain::RangedAttack()
{
	if (bPlayerDead != true)
	{
		FVector projectileSpawnLocation = GetActorLocation() + (GetActorForwardVector()*200.f);
		if(projectile){
			if(PlayerStamina >= 5 && RangedCooldown == false)
			{
				RangedCooldown = true;
				PlayerStamina -= 5;
				GetWorld()->SpawnActor<AProjectile>(projectile, projectileSpawnLocation, GetActorRotation());
				GetWorld()->GetTimerManager().SetTimer(FTHandle, this, &AMain::ResetRangedCooldown, FCoolDownTime, false);
			}
			
		}
	}
}
void AMain::HealAbility()
{
	if(PlayerHealth < 100 && PlayerStamina >= 25 && bPlayerDead != true) // Simple heal ability, if player health is less that 100 and player stamina is more than or equal to 25
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

void AMain::objectpickup() {
	TArray<AActor*> ourcharacter;
	objectpickrange->GetOverlappingActors(ourcharacter);
	float setpower = 0;
	for (int32 collectedpower = 0; collectedpower < ourcharacter.Num(); ++collectedpower) {
		Aobjectspawn* pickupobjectspawn = Cast<Aobjectspawn>(ourcharacter[collectedpower]);
		if (pickupobjectspawn && !pickupobjectspawn->IsPendingKill() && pickupobjectspawn->checkactivation()) {
			pickupobjectspawn->takeit_Implementation();
			AObjectitempickable* pickablecomponent = Cast<AObjectitempickable>(pickupobjectspawn);
			if (pickablecomponent) {
				setpower += pickablecomponent->yourpower();
			}
			pickupobjectspawn->setactivation(false);
		}

	}
	if (setpower > 0) {
		updatemypower(setpower);
	}
}

float AMain::getpower() {
	return currentpower;
}

float AMain::checkmystartingpower() {
	return playercurrentpower;
}

void AMain::updatemypower(float changecurrentpower) {

	playercurrentpower = playercurrentpower + changecurrentpower;

	//change color on power didn't work.
	//GetCharacterMovement()->MaxWalkSpeed = basespeed + speedfactor * playercurrentpower;

	//powerchangevisual(); didn't work

	//if (changecurrentpower > 0) {
		//if (GEngine)
		//{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::SanitizeFloat(changecurrentpower) + FString("power gain"));
		//}
	//}
	//else
	//{
		//if (GEngine)
		//{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::SanitizeFloat(changecurrentpower) + FString("power loss"));
		//}
	//}

}
/*void AMain::powerchangevisual() {
	if (materialpowervisual) {
		float const powerratio = FMath::Clamp((playercurrentpower / currentpower), 0.0f, 1.0f);
		FLinearColor const powerratiocolor = FMath::Lerp(Teal, Orange, powerratio);
		materialpowervisual->SetVectorParameterValue("Param", powerratiocolor);
		GetMesh()->SetMaterial(0, materialpowervisual);
	}
}*/

/*void AMain::secondaryMeele() // i found a code that fit. https://www.youtube.com/watch?v=9yftOwWp48A&t=54s
{ // code from https://www.youtube.com/watch?v=9yftOwWp48A&t=54s
	if (tomeele) {
		UWorld* world = GetWorld();
		if (world) {
			FActorSpawnParameters spawningparameter;
			spawningparameter.Owner = this;
			FRotator rotatingside;
			FVector spawnlocation = this->CameraBoom->GetComponentLocation();
			world->SpawnActor<ACombatarm>(tomeele, spawnlocation, rotatingside, spawningparameter);
		}
	}
}
*/

