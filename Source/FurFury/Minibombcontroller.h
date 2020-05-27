// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Minibombcontroller.generated.h"

/**
 * 
 */
UCLASS()
class FURFURY_API AMinibombcontroller : public AAIController
{
	GENERATED_BODY()

public:
		AMinibombcontroller();
	class UBlackboardComponent* minibombbbc;

	class UBehaviorTreeComponent* minibehaviorc;

	virtual void OnPossess(APawn* pawn) override;

	uint8 bombkey;
};
