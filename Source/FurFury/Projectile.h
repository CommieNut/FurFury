// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class FURFURY_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent * projectile;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class USphereComponent * ColliderComponent;

	UPROPERTY(VisibleAnywhere, Category="Projectile Mesh")
		class UStaticMeshComponent * ProjectileMesh;

	UPROPERTY(EditAnywhere, Category = "Projectile Particles")
		class UParticleSystem * ExplosionParticle;

	UPROPERTY(EditAnywhere, Category = "Projectile Particles")
		class UParticleSystemComponent * ProjectileTrail;
	
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
