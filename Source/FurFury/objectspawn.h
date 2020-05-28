// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "objectspawn.generated.h"

//tutorial from those https://www.youtube.com/watch?v=UfCImpvfDpQ https://www.youtube.com/watch?v=LsNW4FPHuZE https://www.youtube.com/watch?v=2zM3X65Z_J4 https://www.youtube.com/watch?v=mSRov77hNR4&list=RDCMUCBobmJyzsJ6Ll7UbfhI4iwQ&start_radio=1&t=2

UCLASS()
class FURFURY_API Aobjectspawn : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	Aobjectspawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
		class UStaticMeshComponent* objectspawnmodel;

	UFUNCTION(BlueprintPure, Category = "ObjectSpawn")
		bool checkactivation();

	UFUNCTION(BlueprintCallable, Category = "ObjectSpawn")
		void setactivation(bool newobjectspawnstate);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "takeit")
		void takeit();
	virtual void takeit_Implementation();

	//trying to tell my class that it has same function

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool controlactivation;

};
