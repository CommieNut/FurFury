
#include "EnemySpawner.h"
#include "EnemyMinionAI.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Public/TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	spawnbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawnbox"));
	RootComponent = spawnbox;

	spawndelaylowernumber = 10.0f;
	spawndelayhighernumber = 20.0f;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	spawn1to5delay = FMath::FRandRange(spawndelaylowernumber, spawndelayhighernumber);
	GetWorldTimerManager().SetTimer(spawntimer, this, &AEnemySpawner::spawn, spawn1to5delay, false);
	spawn();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//changed to this code due to bug.
void AEnemySpawner::spawn() {
	FVector location = GetActorLocation();
	int counter = 0;
	int currentamount = 3;
	UWorld* world = GetWorld();
	if (world) {
		for (int counter = 0; counter < 2; counter++) {
		}
		if (counter <= currentamount) {
			FActorSpawnParameters spawningparameter;
			spawningparameter.Owner = this;
			FRotator rotatingside;
			FVector spawnlocation = this->spawnbox->GetComponentLocation();
			world->SpawnActor<AEnemyMinionAI>(tospawn, spawnlocation, rotatingside, spawningparameter);
			GetWorldTimerManager().SetTimer(spawntimer, this, &AEnemySpawner::spawn, spawn1to5delay, false);
			counter++;
		}
		else

		{ //need more fix on this part, buggy.
			(counter >= currentamount); {
				delay;
				if (!getdestroyed->Destroy()) {
					counter--;
				}
				
			}
		}

	}
}
