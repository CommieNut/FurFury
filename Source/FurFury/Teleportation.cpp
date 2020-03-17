// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleportation.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Main.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Math/Rotator.h"
#include <iostream>
#include "Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include <sal.h>
#include <vadefs.h>

// Sets default values
ATeleportation::ATeleportation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//some old reference was used and its written on compulsory 1 dont remember link.
	//code learned from isak and dennis and unreal real engine site  https://docs.unrealengine.com/en-US/Programming/Tutorials/PlayerCamera/index.html
    //code changed and work with help of isak reference
	teleportbox = CreateDefaultSubobject<USphereComponent>(TEXT("Teleportbox"));
	RootComponent = teleportbox;
	teleportbox->SetSphereRadius(50.f);
	//teleportbox->GetGenerateOverlapEvents; didn't work and caused error.
	teleportbox->OnComponentBeginOverlap.AddDynamic(this, &ATeleportation::cubeteleport);
	//used ole flaten tutorial to make some changefor teleport to work. got help from reference isak code and dennis.
	model=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("model"));
	model->SetupAttachment(GetRootComponent());
	 

}

// Called when the game starts or when spawned
void ATeleportation::BeginPlay()
{
	Super::BeginPlay();
	
    //SetActorLocationAndRotation(newlocation, newrotation, false, 0, ETeleportType::None);
	//a reference used for making teleport, help came from this site https://www.youtube.com/watch?v=g5EQOzkpWbc
}

// Called every frame
void ATeleportation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATeleportation::cubeteleport(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	//helped by isak and dennis and their code reference and alsohttps://docs.unrealengine.com/en-US/BlueprintAPI/Utilities/Transformation/Teleport/index.html
//https://forums.unrealengine.com/community/community-content-tools-and-tutorials/3103-tutorial-creating-a-teleporter
	//didn't know teleportto existed, made it easy to work.
	AMain* playercharacter = Cast<AMain>(OtherActor);
	if (playercharacter !=NULL) {
		FVector teleportzone = GetActorLocation() + FVector::FVector(0.0f, 0.0f, 100000.0f);
		FRotator rotatzone = playercharacter->GetActorRotation();
		playercharacter->TeleportTo(teleportzone, rotatzone, false, false);

	}

}
//tried this code but it didn't work at all.
//void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	//AActor* OtherActor, UPrimitiveComponent* OtherComp,
	//int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	//if (OtherActor->IsA(AMain::StaticClass())) {
		//OtherActor->SetActorLocation(newlocation);
	//}
//}