// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minibomb.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class FURFURY_API UBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
        /*
public:
     UBTTask_Attack(FObjectInitializer const& object_initializer);

     EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

     bool finished(AMinibomb* const option)*/
};
