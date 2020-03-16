// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FURFURY_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	class APawn* Pawn;
};
