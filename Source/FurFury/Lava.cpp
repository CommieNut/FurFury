// Fill out your copyright notice in the Description page of Project Settings.


#include "Lava.h"
#include "Main.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALava::ALava()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LavaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LavaMesh"));

}

void ALava::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMain* ActorCheck = Cast<AMain>(OtherActor);
	UWorld* World = GetWorld();
	if(IsValid(ActorCheck))
	{
		GetWorld()->GetTimerManager().SetTimer(THandle, this, &ALava::LavaDamage, fDMGpS, true);
	}
}

/*
void ALava::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMain* ActorCheck = Cast<AMain>(OtherActor);
	UWorld* World = GetWorld();
	if (IsValid(ActorCheck))
	{
		World->GetTimerManager().ClearTimer(THandle);
	}
}
*/
void ALava::LavaDamage()
{
	AMain* obj = Cast<AMain>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if(IsValid(obj))
	{
		obj->PlayerHealth = 0;
	}	
}

// Called when the game starts or when spawned
void ALava::BeginPlay()
{
	Super::BeginPlay();
	LavaMesh->OnComponentBeginOverlap.AddDynamic(this, &ALava::OnBeginOverlap);
	//LavaMesh->OnComponentEndOverlap.AddDynamic(this, &ALava::OnEndOverlap);
}

// Called every frame
void ALava::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

