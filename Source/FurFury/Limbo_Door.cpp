// Fill out your copyright notice in the Description page of Project Settings.


#include "Limbo_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Main.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

// Sets default values
ALimbo_Door::ALimbo_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	SetRootComponent(DoorMesh);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->AddLocalOffset(FVector(0.f, 0.f, 0.f));
	CollisionSphere->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ALimbo_Door::OnBeginOverlap);
	
}
	

void ALimbo_Door::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Overlap"));
	AMain* Player = Cast<AMain>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (IsValid(Player) && Player->KeysCollected == 3 && bDoorCanMove) {
		UE_LOG(LogTemp, Warning, TEXT("DoorOpen"));
		SetActorRotation(FRotator(0.0f, 60.0f, 0.0f));
		AddActorLocalOffset(FVector(-60.0f ,-200.0f, 0.0f));
		bDoorCanMove = false;
	}
}

// Called when the game starts or when spawned
void ALimbo_Door::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALimbo_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

