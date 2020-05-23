// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Lava.generated.h"

UCLASS()
class FURFURY_API ALava : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALava();
	FTimerHandle THandle;
	
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UStaticMeshComponent* LavaMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LavaDamagePerSecond")
		float fDMGpS = 0.1f;

	AActor* ActorToBurn;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
//	UFUNCTION()
//		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void LavaDamage();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
