// Fill out your copyright notice in the Description page of Project Settings.


#include "objectspawn.h"
#include "Components/MeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

// Sets default values  //tutorial from those https://www.youtube.com/watch?v=UfCImpvfDpQ https://www.youtube.com/watch?v=LsNW4FPHuZE https://www.youtube.com/watch?v=2zM3X65Z_J4 https://www.youtube.com/watch?v=mSRov77hNR4&list=RDCMUCBobmJyzsJ6Ll7UbfhI4iwQ&start_radio=1&t=2

Aobjectspawn::Aobjectspawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	controlactivation = true;

	objectspawnmodel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Objectspawn"));
	RootComponent = objectspawnmodel;

	//this actor is create for purpose of no physics and use with activation and deactivation function.
	//this actor is going to be used as parent of a child for another actor
}

// Called when the game starts or when spawned
void Aobjectspawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void Aobjectspawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// control of activation. can also be used in blueprint for deactivation purpose
bool Aobjectspawn::checkactivation() {
	return controlactivation;
}

void Aobjectspawn::setactivation(bool newobjectspawnstate) {
	controlactivation = newobjectspawnstate;
}

//to check if it work.
void Aobjectspawn::takeit_Implementation() {
	FString takeitdebug = GetName();
	UE_LOG(LogClass, Log, TEXT("you have takenobject"), *takeitdebug);
}
