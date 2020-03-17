// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//helped by isak and dennis
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = Collision;
	
	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float enemypawntime)
{
	Super::Tick(enemypawntime);
	FVector direction = GetActorLocation() + FVector(1.0f, 0.0f, 0.0f); // https://forums.unrealengine.com/development-discussion/c-gameplay-programming/30572-need-help-vector-riddle , https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FVector/GetSafeNormal/index.html , https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FVector/index.html
	FVector myenemyactordefaultplace = direction + enemypawntime; // https://docs.unrealengine.com/en-US/Programming/Tutorials/PlayerInput/index.html
	SetActorLocation(myenemyactordefaultplace); // https://docs.unrealengine.com/en-US/Programming/Tutorials/PlayerInput/index.html

}


