 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_secretcheck.generated.h"

/**
 * 
 */
UCLASS()
class FURFURY_API UBTService_secretcheck : public UBTService
{
	GENERATED_BODY()
public:
    UBTService_secretcheck();
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
