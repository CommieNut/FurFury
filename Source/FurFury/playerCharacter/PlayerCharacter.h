// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FURFURY_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Variables")
		int HP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Variables")
		int Mana;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Variables")
		int Level;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent * PlayerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent * Camera;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
