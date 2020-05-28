
#include "EnemySpawner.h"
#include "EnemyMinionAI.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Public/TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MainRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefRootComp"));
	SetRootComponent(MainRootComponent);
	
	spawnbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawnbox"));
	spawnbox->SetupAttachment(RootComponent);
}



// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bInfiniteSpawns){
		UE_LOG(LogTemp, Warning, TEXT("Using Unlimited Spawns"))
		ReadyToSpawn = true;
	}else if(!bInfiniteSpawns && AmountOfActors > 0){
		UE_LOG(LogTemp, Warning, TEXT("Using Limited Spawns: Amount Of Actors Left To Spawn %d"), AmountOfActors);
		ReadyToSpawn = true;
	}else{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Stopped"))
		ReadyToSpawn = false;
	}

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Spawner Exists"))

		if (RandomTimerMinMax)
		{
			UE_LOG(LogTemp, Warning, TEXT("Using Dyminc Random Delay MIN/MAX"))
				Final = FMath::FRandRange(LocalRandomDelayInSecondsMin, LocalRandomDelayInSecondsMax); // get from handler
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Using Static Preset Delay"))
				Final = LocalPreSetDelayInSeconds;
		}
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::spawn, Final, ReadyToSpawn);
}


//changed to this code due to bug.
void AEnemySpawner::spawn() {
	UWorld* world = GetWorld();
	FRotator rotatingside = UKismetMathLibrary::RandomRotator();
	if(!SpawnLocationRandomWithinBoxLimits)
	{
		UE_LOG(LogTemp, Warning, TEXT("Using Exact Location"))
		FVector spawnlocation = RootComponent->GetComponentLocation();	
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("Using Random Location Within An Area"))
		FVector spawnlocation = UKismetMathLibrary::RandomPointInBoundingBox(RootComponent->GetComponentLocation(), spawnbox->GetScaledBoxExtent());
	}

	
	if (world) {
			UE_LOG(LogTemp, Warning, TEXT("Spawning"))
			world->SpawnActor<ACharacter>(ActorToSpawn, spawnlocation, rotatingside);
	}
}

