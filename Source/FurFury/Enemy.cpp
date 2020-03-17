// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
<<<<<<< HEAD
#include "Components/BoxComponent.h"
=======
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
>>>>>>> yearlyfruit

// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
<<<<<<< HEAD

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Collision->SetupAttachment(GetRootComponent());
	Collision->GetGenerateOverlapEvents();
=======
	//helped by isak and dennis
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = Collision;
	
	MeshComponent->SetupAttachment(RootComponent);
>>>>>>> yearlyfruit
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
<<<<<<< HEAD
	//Collision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/*
void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Melee attack HIT"));

}
*/
=======
}

// Called every frame
void AEnemy::Tick(float enemypawntime)
{
	Super::Tick(enemypawntime);
	FVector direction = GetActorLocation() + FVector(1.0f, 0.0f, 0.0f); // https://forums.unrealengine.com/development-discussion/c-gameplay-programming/30572-need-help-vector-riddle , https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FVector/GetSafeNormal/index.html , https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FVector/index.html
	FVector myenemyactordefaultplace = direction + enemypawntime; // https://docs.unrealengine.com/en-US/Programming/Tutorials/PlayerInput/index.html
	SetActorLocation(myenemyactordefaultplace); // https://docs.unrealengine.com/en-US/Programming/Tutorials/PlayerInput/index.html

}
>>>>>>> yearlyfruit


