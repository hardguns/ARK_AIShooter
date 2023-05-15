// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STS_BaseCharacter.generated.h"

class ASTS_Weapon;
class USTS_HealthComponent;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASTS_BaseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USTS_HealthComponent* HealthComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsMeleeAttacking;

	UFUNCTION(BlueprintCallable)
	void StartMelee();

	UFUNCTION(BlueprintCallable)
	void FinishMelee(UAnimMontage* AnimMontage, bool bIsInterrupted);

	UFUNCTION(BlueprintCallable)
	void DoMeleeAttack();

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTS_Weapon> StartingWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Weapon")
	ASTS_Weapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	UAnimMontage* MeleeAttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	FName MeleeAttackBoneName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float MeleeAttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	TArray<TEnumAsByte<EObjectTypeQuery>> MeleeObjectTypes;

	UPROPERTY(Transient)
	UAnimInstance* AnimInstance;

	virtual void BeginPlay() override;

	void AttachWeaponToCharacter();

	UFUNCTION()
	void OnHealthChanged(USTS_HealthComponent* HealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnDeath(USTS_HealthComponent* HealthComp, class AController* InstigatedBy, AActor* Killer);

};
