// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STS_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChanged, USTS_HealthComponent*, HealthComponent, float, Health, float, HealthDelta, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDeath, USTS_HealthComponent*, HealthComponent, class AController*, InstigatedBy, AActor*, Killer);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARK_STEALTHSHOOTER_API USTS_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USTS_HealthComponent();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	UFUNCTION(BlueprintCallable)
	void Kill(AController* InstigatedBy, AActor* DamageCauser);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	bool bDied;

	UPROPERTY(EditDefaultsOnly)
	float DefaultHealth;
	
	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

};
