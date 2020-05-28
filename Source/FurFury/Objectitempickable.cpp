
#include "Objectitempickable.h"
#include "FurFury.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "objectspawn.h"
// Sets default values
//tutorial from those https://www.youtube.com/watch?v=UfCImpvfDpQ https://www.youtube.com/watch?v=LsNW4FPHuZE https://www.youtube.com/watch?v=2zM3X65Z_J4 https://www.youtube.com/watch?v=mSRov77hNR4&list=RDCMUCBobmJyzsJ6Ll7UbfhI4iwQ&start_radio=1&t=2

AObjectitempickable::AObjectitempickable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	powervalue = 155.f;

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