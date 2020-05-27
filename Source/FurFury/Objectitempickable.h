// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "objectspawn.h"
#include "Objectitempickable.generated.h"

/**
 *
 */
UCLASS()
class FURFURY_API AObjectitempickable : public Aobjectspawn
{
	GENERATED_BODY()
public:
	// Called when the game starts or when spawned
	AObjectitempickable();

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void takeit_Implementation() override;

	float yourpower();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "powervalue")
		float powervalue;

protected:
	//true for when pickup can be used and false to be deactived.


};
// Fill out your copyright notice in the Description page of Project Settings.

