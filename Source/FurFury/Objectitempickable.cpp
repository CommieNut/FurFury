
#include "Objectitempickable.h"
#include "FurFury.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "objectspawn.h"
// Sets default values

AObjectitempickable::AObjectitempickable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	powervalue = 150.f;

}

void AObjectitempickable::BeginPlay()
{
	Super::BeginPlay();
	//sets this child component to simulate physics.
	//objectspawnmodel->SetSimulatePhysics(true);
}

// Called every frame
void AObjectitempickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// gaining power.
void AObjectitempickable::takeit_Implementation() {
	Super::takeit_Implementation();
	Destroy();
}

float AObjectitempickable::yourpower() {
	return powervalue;
}