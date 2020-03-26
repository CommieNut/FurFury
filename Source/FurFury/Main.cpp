// Fill out your copyright notice in the Description page of Project Settings.
#include "Main.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Enemy.h"

// Sets default values
AMain::AMain()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Creates the invisible sphere component we use as a hitbox to detect collision on key press. (Doesnt work yet)
	MeleeHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("MeleeHitbox"));
	MeleeHitbox->SetupAttachment(GetRootComponent());
	MeleeHitbox->AddLocalOffset(FVector(80.f, 0.f, 0.f));

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

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom, and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;


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
	GetCharacterMovement()->AirControl = 0.2f; // (Kanskje burde fjerne air control... -Mo 19.03.2020)

	AutoPossessPlayer = EAutoReceiveInput::Player0; // Assume immediate control of character without having to set it up in project settings
}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &AMain::MeleeAttack);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);
}


void AMain::MoveForward(float Value)
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
void AMain::MoveRight(float Value)
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
void AMain::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMain::MeleeAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee Attack!"));
	TArray<AActor*> TempActors;
	MeleeHitbox->GetOverlappingActors(TempActors, AEnemy::StaticClass());
	for (size_t i = 0; i < TempActors.Num(); i++)
	{
		TempActors[i]->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Enemy Destroyed!"));
	}
}
