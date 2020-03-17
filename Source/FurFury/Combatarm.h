// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Combatarm.generated.h"

UCLASS()
class FURFURY_API ACombatarm : public AActor
{
	GENERATED_BODY()
		
	//	UPROPERTY(VisibleAnywhere)
	//	class USphereComponent* Bullet;

	//UPROPERTY(EditAnywhere, Category = "Mesh")
	//	class UStaticMeshComponent* Mesh;
	//UPROPERTY()
		//FTimerHandle DespawnTimer;
	//UPROPERTY()
		//float Delay;

public:	
	// Sets default values for this actor's properties
	ACombatarm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BulletExpired();

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	//ole flaten exemplar tutorial and code.
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* killedcolli;
	//UPROPERTY(VisibleAnywhere)
		 //class UCapsuleComponent* Killcollision;
	//UPROPERTY(VisibleAnywhere)
		 //class UBoxComponent* killcollision;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* flying;
	//UPROPERTY(EditAnywhere)
		//float speed{ 400.f };
};
