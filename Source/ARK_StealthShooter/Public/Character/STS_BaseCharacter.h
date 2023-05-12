// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STS_BaseCharacter.generated.h"

class ASTS_Weapon;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASTS_BaseCharacter();

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTS_Weapon> StartingWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName;

	UPROPERTY(BlueprintReadOnly, Transient)
	ASTS_Weapon* CurrentWeapon;

	UFUNCTION(BlueprintCallable)
	void StartFire();

protected:

	virtual void BeginPlay() override;

	void AttachWeaponToCharacter();

};
