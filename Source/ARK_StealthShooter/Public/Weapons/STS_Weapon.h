// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STS_Weapon.generated.h"

class UStaticMeshComponent;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ASTS_Weapon();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float ShotDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float ShotDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	TSubclassOf<UDamageType> WeaponDamageType;

	virtual void BeginPlay() override;

public:

	void Fire();

};
