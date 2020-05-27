// Fill out your copyright notice in the Description page of Project Settings.


#include "Minibombcontroller.h"

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

//tried to learn from these video and site, but only one worked https://docs.unrealengine.com/en-US/Engine/AI/BehaviorTrees/QuickStart/5/index.html https://www.youtube.com/watch?v=3Z1A825gTA8 https://www.youtube.com/watch?v=fzgvXgHuxL4 https://www.youtube.com/watch?v=t-uiTbEUl00&list=PLWUvrI0mg8VLrvq3n2iu45lhCo69uluDK&index=2

AMinibombcontroller::AMinibombcontroller() {

	minibombbbc = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboards"));

	minibehaviorc = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behaviortreez"));
}
void AMinibombcontroller::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	AMinibomb* bomb = Cast<AMinibomb>(pawn);
	if (bomb) {
		minibombbbc->InitializeBlackboard(*bomb->bombbehavior->BlackboardAsset);

		bombkey = minibombbbc->GetKeyID("DestroyAMain");

		minibehaviorc->StartTree(*bomb->bombbehavior);
	}
}
