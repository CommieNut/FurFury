
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
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	Final = FMath::FRandRange(LocalRandomDelayInSecondsMin, LocalRandomDelayInSecondsMax); // get from handler
	
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::spawn, Final, false);
	spawn();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//changed to this code due to bug.
void AEnemySpawner::spawn() {
	UWorld* world = GetWorld();
	FRotator rotatingside;
	FVector spawnlocation = this->spawnbox->GetComponentLocation();
	FActorSpawnParameters spawningparameter;
	spawningparameter.Owner = this;
	if (world) {
			world->SpawnActor<AEnemyMinionAI>(ActorToSpawn, spawnlocation, rotatingside, spawningparameter);
	}
}
