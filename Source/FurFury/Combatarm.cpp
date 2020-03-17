// Fill out your copyright notice in the Description page of Project Settings.


#include "Combatarm.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Main.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACombatarm::ACombatarm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// ole flaten code from exemplar and https://docs.unrealengine.com/en-US/Programming/Tutorials/PlayerInput/index.html
	killedcolli = CreateDefaultSubobject<USphereComponent>(TEXT("killcolli"));

	//killcollision=CreateDefaultSubobject<UBoxComponent>(TEXT("KillCollision"));
	//killcollision=CreateDefaultSuboject<UCapsuleComponent>(TEXT("KillCollision"));

	killedcolli->OnComponentBeginOverlap.AddDynamic(this, &ACombatarm::OnOverlap);
	killedcolli->SetSphereRadius(200.f);

	//difficult to change, code that didn't work.
	//Killcollision->SetBoxExtent(50.0f);
	//killcollision->SetCapsuleComponent;

	RootComponent = killedcolli;

	flying = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("flying"));
	flying->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACombatarm::BeginPlay()
{
	Super::BeginPlay();

	//GetWorldTimerManager().SetTimer(DespawnTimer, this, &ACombatarm::BulletExpired, Delay);
	
}


// Called every frame
void ACombatarm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	//AddActorLocalOffset(FVector(500.f, 0.f, 0.f) * DeltaTime);
	FVector direction = GetActorLocation() + FVector(10.0f, 0.0f, 0.0f); // https://forums.unrealengine.com/development-discussion/c-gameplay-programming/30572-need-help-vector-riddle , https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FVector/GetSafeNormal/index.html , https://docs.unrealengine.com/en-US/API/Runtime/Core/Math/FVector/index.html
	FVector myspawnpoint = direction + DeltaTime; // 
	SetActorLocation(myspawnpoint); //
	//FVector newlocation = GetActorLocation();
	//newlocation += GetActorForwardVector() * speed * DeltaTime;
	//SetActorLocation(newlocation);

}
//forgot to use this, oh well.
void ACombatarm::BulletExpired()
{
	Destroy();
}
void ACombatarm::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor->IsA(AEnemy::StaticClass())) {
		OtherActor->Destroy();

		Destroy();
	}
}
