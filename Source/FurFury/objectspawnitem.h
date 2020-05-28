// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "objectspawnitem.generated.h"
//tutorial from those https://www.youtube.com/watch?v=UfCImpvfDpQ https://www.youtube.com/watch?v=LsNW4FPHuZE https://www.youtube.com/watch?v=2zM3X65Z_J4 https://www.youtube.com/watch?v=mSRov77hNR4&list=RDCMUCBobmJyzsJ6Ll7UbfhI4iwQ&start_radio=1&t=2

UCLASS()
class FURFURY_API Aobjectspawnitem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	Aobjectspawnitem();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "objectitemspawn")
		class UBoxComponent* objectlocationmodel;
	UFUNCTION(BlueprintPure, Category = "RandomFactor")
		FVector getrandomplace();
	UPROPERTY(EditAnywhere, Category = "spawningthemodel")
		TSubclassOf<class Aobjectspawn> appear;
	FTimerHandle appeartimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "appeartimehandling")
		float appeartimerdelaylower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "appeartimehandling")
		float appeartimedelaybigger;

	UFUNCTION(BlueprintCallable, Category = "togglefunction")
		void setspawningactive(bool whentospawn);

	void spawnitem();

	float timethirdfactor;

protected:

};