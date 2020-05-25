// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

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

	
	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion Particle"));
	ExplosionParticle->SetupAttachment(ColliderComponent);
	
	ProjectileTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle"));
	ExplosionParticle->SetupAttachment(ColliderComponent);
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
	if(ExplosionParticle)
	{
		ExplosionParticle->Activate();
	}
	this->Destroy();
}