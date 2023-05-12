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

	void StartFire();

	void StopFire();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float ShotDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float ShotDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (ClampMin=0.1f))
	float RoundsPerMinute;

	float TimeBetweenShots;

	float LastFireTime;

	FTimerHandle TimerHandle_AutoFire;

	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	bool bDrawDebug;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* TraceEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	FName TraceTargetName;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	TSubclassOf<UDamageType> WeaponDamageType;

	void Fire();

	virtual void BeginPlay() override;

};
