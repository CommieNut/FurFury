
#include "Keymodetest.h"
#include "Main.h"
#include "FurFury.h"
#include "UObject/ConstructorHelpers.h"
#include "DefaultPawn.generated.h"
#include "Kismet/GameplayStatics.h"
#include "Gameframework/GameMode.h"
#include "Objectitempickable.h"
#include "objectspawn.h"
#include "objectspawnitem.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "EngineUtils.h"
//tutorial from those https://www.youtube.com/watch?v=UfCImpvfDpQ https://www.youtube.com/watch?v=LsNW4FPHuZE https://www.youtube.com/watch?v=2zM3X65Z_J4 https://www.youtube.com/watch?v=mSRov77hNR4&list=RDCMUCBobmJyzsJ6Ll7UbfhI4iwQ&start_radio=1&t=2

// a difficulty mode for losing power, or trying out before making a trap that reduce power 
AKeymodetest::AKeymodetest() {

	static ConstructorHelpers::FClassFinder<APawn>thisishard(TEXT("/Game/Blueprints/MyMain.MyMain"));
	if (thisishard.Class != NULL) {
		DefaultPawnClass = thisishard.Class;

	}
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	slowpowerlose = 0.0f;
}
//most annoying code to make it work.
void AKeymodetest::BeginPlay()
{
	Super::BeginPlay();
	setcurrentstate(EpowerPlayState::EPlaying);
	TArray<AActor*> allactor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Aobjectspawnitem::StaticClass(), allactor);
	for (auto Actor : allactor) {
		Aobjectspawnitem* spawnbut = Cast<Aobjectspawnitem>(Actor);
		if (spawnbut) {
			spawnbutton.AddUnique(spawnbut);


		}
		//targetoflosingmana = Cast<AMain>(UGameplayStatics::GetPlayerPawn(this, 0));
		/*targetoflosingmana = Cast<AMain>(UGameplayStatics::GetPlayerPawn(this, 0));
		if (targetoflosingmana) {
			if (targetoflosingmana->getpower() > 0) {
				targetoflosingmana->updatemypower(-1*hunger*(targetoflosingmana->getpower()));
			}

		}**/
		//GetWorldTimerManager().SetTimer(updatingmypower, this, &AMain::getpower, Delay);

		//set win condition
		targetoflosingmana = Cast<AMain>(UGameplayStatics::GetPlayerPawn(this, 0));
		if (targetoflosingmana) {
			winconditionwithpower = (targetoflosingmana->getpower()) * 1.10f;
		}
		if (HudWidgetClass != nullptr) {
			UUserWidget* firstwidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
			if (firstwidget != nullptr) {
				firstwidget->AddToViewport();
			}
		}

		//for (TActorIterator<Aobjectspawnitem>it(GetWorld());it;++it) {
		//	spawnbutton.Add(*it);
		//}
	}
}

//just a code for testing. if it work be used. it finally work so annoying!
void AKeymodetest::Tick(float Deltatime) {
	Super::Tick(Deltatime);
	targetoflosingmana = Cast<AMain>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (targetoflosingmana) {
		if (targetoflosingmana->playercurrentpower > winconditionwithpower) {
			setcurrentstate(EpowerPlayState::EWon);
			///write something here? any code that move a object? oh wait i dont have the gate in the c++, ja blueprint/in unreal  nei bare blueprint og unreal map
		}
		else if (targetoflosingmana->playercurrentpower > 0) {
			targetoflosingmana->updatemypower(-Deltatime * slowpowerlose * (targetoflosingmana->getpower()));

		}
		else {
			setcurrentstate(EpowerPlayState::EGameOver);
		}
	}
}



float AKeymodetest::getwinobject() {
	return winconditionwithpower;
}

EpowerPlayState AKeymodetest::getcurrentstate() {
	return currentstate;
}

void AKeymodetest::setcurrentstate(EpowerPlayState newz) {
	currentstate = newz;
	handling(currentstate);
}

void AKeymodetest::handling(EpowerPlayState newz) {

	switch (newz)
	{
	case EpowerPlayState::EPlaying:
	{
		for (Aobjectspawnitem* spawnfactor : spawnbutton) {
			spawnfactor->setspawningactive(true);
		}
	}
	break;

	case EpowerPlayState::EWon: {
		for (Aobjectspawnitem* spawnfactor : spawnbutton) {
			spawnfactor->setspawningactive(false);
		}
		
		}
	
	break;

	case EpowerPlayState::EGameOver:
	{
		for (Aobjectspawnitem* spawnfactor : spawnbutton) {
			spawnfactor->setspawningactive(false);
		}
	}
	break;

	default:
	case EpowerPlayState::EUnknown:
	{
		//return nothing
	}
	break;
	}

}