// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class FURFURY_API AEnemy : public AActor
{
	GENERATED_BODY()
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

