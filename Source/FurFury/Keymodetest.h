#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Keymodetest.generated.h"

//tutorial from those https://www.youtube.com/watch?v=UfCImpvfDpQ https://www.youtube.com/watch?v=LsNW4FPHuZE https://www.youtube.com/watch?v=2zM3X65Z_J4 https://www.youtube.com/watch?v=mSRov77hNR4&list=RDCMUCBobmJyzsJ6Ll7UbfhI4iwQ&start_radio=1&t=2

//store state variable
UENUM(BlueprintType)
enum class EpowerPlayState : uint8
{
	EPlaying UMETA(DisplayName = "Playing"),
	EGameOver UMETA(Displayname = "Game Over"),
	EWon UMETA(DisplayName = "Won"),
	EUnknown UMETA(DisplayName = "Unknown")
};

UCLASS()
class FURFURY_API AKeymodetest : public AGameModeBase
{
	GENERATED_BODY() //still has redlines, but complied ok? thats annoying.

public:
	AKeymodetest();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "power")
		float slowpowerlose;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	class AMain* targetoflosingmana;

	//const is to prevent other c++ code from messing with value
	//win variable testing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "win condition")
		float winconditionwithpower;

	UFUNCTION(BlueprintPure, Category = "win condition power")
		float getwinobject();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "win widget")
		TSubclassOf<class UUserWidget> HudWidgetClass;


	class UUserWidget* firstwidget;

	TArray<class Aobjectspawnitem*> spawnbutton;

	void handling(EpowerPlayState newz);

	//keeping track of the game
	EpowerPlayState currentstate;

	UFUNCTION(BlueprintPure, Category = "power")
		EpowerPlayState getcurrentstate();

	void  setcurrentstate(EpowerPlayState newz);

};
