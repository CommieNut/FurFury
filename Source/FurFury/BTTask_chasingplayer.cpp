// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_chasingplayer.h"

// Fill out your copyright notice in the Description page of Project Settings.



#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Components/StaticMeshComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Minibomb.h"
#include "Minibombcontroller.h"
#include "Main.h"
#include "BTTask_chasingplayer.h"

//tried to learn from these video and site, but only one worked https://docs.unrealengine.com/en-US/Engine/AI/BehaviorTrees/QuickStart/5/index.html https://www.youtube.com/watch?v=3Z1A825gTA8 https://www.youtube.com/watch?v=fzgvXgHuxL4 https://www.youtube.com/watch?v=t-uiTbEUl00&list=PLWUvrI0mg8VLrvq3n2iu45lhCo69uluDK&index=2

EBTNodeResult::Type UBTTask_chasingplayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AMinibombcontroller* bombcharacter = Cast<AMinibombcontroller>(OwnerComp.GetAIOwner());
	AMain* furfurchar = Cast<AMain>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(bombcharacter->bombkey));
	if (furfurchar) {
			bombcharacter->MoveToActor(furfurchar, 10.f, true, true, true, 0, true);
			return EBTNodeResult::Succeeded;
	}
	else {
			return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}



