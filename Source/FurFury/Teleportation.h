// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleportation.generated.h"

UCLASS()
class FURFURY_API ATeleportation : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere)
		class USphereComponent* teleportbox;
	UPROPERTY(EditAnywhere, Category = "model") //code learned by classmate isak/dennis
		class UStaticMeshComponent* model;
	//UPROPERTY(EditAnywhere, Category = "sound")
		//class USoundCue* teleportingsound;
	UPROPERTY(VisibleAnywhere, Category = "CollisionCapsule") //code learned by classmate isak/dennis
		class USphereComponent* collision;

  
public:	
	// Sets default values for this actor's properties
	ATeleportation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//reference from this https://www.youtube.com/watch?v=g5EQOzkpWbc
	//UPROPERTY(EditAnywhere, Category = "Teleport location")
		//FVector newlocation;
	//UPROPERTY(EditAnywhere, Category = "Teleport location")
		//FQuat newrotation;
  UFUNCTION(BlueprintCallable, Category = "teleport") //code learned from isak and dennis
		void cubeteleport(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

};