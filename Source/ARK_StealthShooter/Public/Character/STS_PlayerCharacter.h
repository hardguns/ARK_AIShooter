// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/STS_BaseCharacter.h"
#include "STS_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_PlayerCharacter : public ASTS_BaseCharacter
{
	GENERATED_BODY()

public:

	ASTS_PlayerCharacter();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void StartCrouch();

	void EndCrouch();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;
	
};
