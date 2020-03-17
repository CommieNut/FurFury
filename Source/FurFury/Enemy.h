// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class FURFURY_API AEnemy : public AActor
{
	GENERATED_BODY()
<<<<<<< HEAD

public:
	// Sets default values for this actor's properties
	AEnemy();
=======
public:
	// Sets default values for this actor's properties
	AEnemy();
	
	virtual void Tick(float enemypawntime) override;
	//helped by isak and dennis

UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;

		UPROPERTY(VisibleAnywhere, Category = "Collision | Capsule")
		class UCapsuleComponent* Collision;	
	
private:
>>>>>>> yearlyfruit

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

<<<<<<< HEAD
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//The enemy Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class UBoxComponent* Collision;

	/*
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	*/
=======
>>>>>>> yearlyfruit
};

