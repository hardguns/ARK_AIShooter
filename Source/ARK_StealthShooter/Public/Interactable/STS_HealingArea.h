// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STS_HealingArea.generated.h"

class UStaticMeshComponent;
class ASTS_BaseCharacter;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_HealingArea : public AActor
{
	GENERATED_BODY()
	
public:	

	ASTS_HealingArea();

	UPROPERTY()
	uint8 bIsActive : 1;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* AreaMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float HealingAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float CooldownTime;

	FTimerHandle TimerHandle_Cooldown;

	void Heal(ASTS_BaseCharacter* HealCharacter);

	void Reset();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
