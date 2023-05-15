// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STS_HealthComponent.h"

//--------------------------------------------------------------------------------------------------------------------
USTS_HealthComponent::USTS_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100.f;
	bDied = false;
}

//--------------------------------------------------------------------------------------------------------------------
void USTS_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = DefaultHealth;

	AActor* ActorOwner = GetOwner();
	if (IsValid(ActorOwner))
	{
		ActorOwner->OnTakeAnyDamage.AddDynamic(this, &USTS_HealthComponent::HandleTakeAnyDamage);
	}
}

//--------------------------------------------------------------------------------------------------------------------
void USTS_HealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f || bDied)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, DefaultHealth);
	OnHealthChanged.Broadcast(this, CurrentHealth, Damage, DamageType, InstigatedBy, DamageCauser);

	if (CurrentHealth <= 0.f)
	{
		bDied = true;
		OnDeath.Broadcast(this, InstigatedBy, DamageCauser);
	}
}

//--------------------------------------------------------------------------------------------------------------------
void USTS_HealthComponent::Kill(AController* InstigatedBy, AActor* DamageCauser)
{
	if (bDied)
	{
		return;
	}

	CurrentHealth = 0.f;
	bDied = true;
	OnDeath.Broadcast(this, InstigatedBy, DamageCauser);
}
