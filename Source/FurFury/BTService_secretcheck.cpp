// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_secretcheck.h"
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
#include "Minibombcontroller.h"
#include "Minibomb.h"
#include "FurFury.h"
#include "Main.h"
#include "Engine/Engine.h"


//tried to learn from these video and site, but only one worked https://docs.unrealengine.com/en-US/Engine/AI/BehaviorTrees/QuickStart/5/index.html https://www.youtube.com/watch?v=3Z1A825gTA8 https://www.youtube.com/watch?v=fzgvXgHuxL4 https://www.youtube.com/watch?v=t-uiTbEUl00&list=PLWUvrI0mg8VLrvq3n2iu45lhCo69uluDK&index=2
UBTService_secretcheck::UBTService_secretcheck() {
	bCreateNodeInstance = true;
}

void UBTService_secretcheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

	AMinibombcontroller* bombcharacter = Cast<AMinibombcontroller>(OwnerComp.GetAIOwner());
	if (bombcharacter) {
		AMain* furfurchar = Cast<AMain>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (furfurchar) {
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(bombcharacter->bombkey, furfurchar);
		}
	}
}