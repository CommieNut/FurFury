// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup_Stamina.h"

// Sets default values
APickup_Stamina::APickup_Stamina()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickup_Stamina::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup_Stamina::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

