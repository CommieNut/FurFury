// Fill out your copyright notice in the Description page of Project Settings.


#include "Key_BP.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AKey_BP::AKey_BP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	HaloMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HaloMesh"));
	SetRootComponent(KeyMesh);

	HaloMesh->SetupAttachment(KeyMesh);
}

// Called when the game starts or when spawned
void AKey_BP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKey_BP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

