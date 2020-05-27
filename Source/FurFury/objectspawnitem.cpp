// Fill out your copyright notice in the Description page of Project Settings.


#include "objectspawnitem.h"
#include "Public/TimerManager.h"
#include "Kismet/kismetMathLibrary.h"
#include "Objectspawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
Aobjectspawnitem::Aobjectspawnitem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	objectlocationmodel = CreateDefaultSubobject<UBoxComponent>(TEXT("Objectmodel"));
	RootComponent = objectlocationmodel;

	appeartimerdelaylower = 5.0f;
	appeartimedelaybigger = 15.0f;
}

// Called when the game starts or when spawned
void Aobjectspawnitem::BeginPlay()
{
	Super::BeginPlay();
	setspawningactive(true);
}

// Called every frame
void Aobjectspawnitem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Fill out your copyright notice in the Description page of Project Settings.


FVector Aobjectspawnitem::getrandomplace() {
	FVector firstarea = objectlocationmodel->Bounds.Origin;
	FVector extending = objectlocationmodel->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(firstarea, extending);

}

void Aobjectspawnitem::setspawningactive(bool whentospawn) {

	if (whentospawn)
	{
		//start
		timethirdfactor = FMath::FRandRange(appeartimerdelaylower, appeartimedelaybigger);
		GetWorldTimerManager().SetTimer(appeartimer, this, &Aobjectspawnitem::spawnitem, timethirdfactor, false);
	}
	else
	{
		//stop
		GetWorldTimerManager().ClearTimer(appeartimer);
	}
}

void Aobjectspawnitem::spawnitem() {
	if (appear != NULL) {
		UWorld* world = GetWorld();
		if (world) {
			FActorSpawnParameters objectplace;
			objectplace.Owner = this;
			objectplace.Instigator = Instigator;

			FVector callforrandom = getrandomplace();

			FRotator angling;
			angling.Yaw = FMath::FRand() * 360.0f;
			angling.Pitch = FMath::FRand() * 360.0f;
			angling.Roll = FMath::FRand() * 360.0f;

			Aobjectspawn* appearfactor = world->SpawnActor<Aobjectspawn>(appear, callforrandom, angling, objectplace);
			GetWorldTimerManager().SetTimer(appeartimer, this, &Aobjectspawnitem::spawnitem, timethirdfactor, false);


		}
	}
}