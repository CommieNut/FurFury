// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "EnemyMinionAI.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Pluton.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	projectile->InitialSpeed = 1000.f;
	projectile->MaxSpeed = 1000.f;
	projectile->bRotationFollowsVelocity = true;
	projectile->ProjectileGravityScale = 0.f;

	ColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collider Component"));
	SetRootComponent(ColliderComponent);
	ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(ColliderComponent);

	ProjectileTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileTrail"));
	ProjectileTrail->SetupAttachment(ColliderComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Melee Attack!"));
	TArray<AActor*> TempActors; // Make an array to contain colliding actors
	ColliderComponent->GetOverlappingActors(TempActors, APawn::StaticClass());
	if(ExplosionParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation(), GetActorRotation(), true, EPSCPoolMethod::None, true);
	}
	for (size_t i = 0; i < TempActors.Num(); i++) // runs through the array
	{
		//TempActors[i]->Destroy(); // Destroy actor in that specefic array index
		auto enemyActor1 = Cast<AEnemyMinionAI>(TempActors[i]);
		auto enemyActor2 = Cast<APluton>(TempActors[i]);
		auto enemyActor3 = Cast<AMain>(TempActors[i]);
		if (IsValid(enemyActor1))
		{
			enemyActor1->minionHealth -= 50;
			//			enemyActor->deathFunction();
		}else if(IsValid(enemyActor2))
		{
			enemyActor2->Destroy();
		}else if(IsValid(enemyActor3))
		{
			enemyActor3->PlayerHealth -= 25;
		}
	}
	this->Destroy();
}