// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/STS_BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Weapons/STS_Weapon.h"
#include "Components/STS_HealthComponent.h"
#include "Kismet/KismetSystemLibrary.h"

//--------------------------------------------------------------------------------------------------------------------
ASTS_BaseCharacter::ASTS_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	HealthComponent = CreateDefaultSubobject<USTS_HealthComponent>(TEXT("HealthComponent"));

}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_BaseCharacter::StartMelee()
{
	if (bIsMeleeAttacking)
	{
		return;
	}

	if (IsValid(AnimInstance))
	{
		bIsMeleeAttacking = true;
		GetMovementComponent()->StopMovementImmediately();
		AnimInstance->Montage_Play(MeleeAttackMontage);
	}
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_BaseCharacter::FinishMelee(UAnimMontage* AnimMontage, bool bIsInterrupted)
{
	if (AnimMontage == MeleeAttackMontage)
	{
		bIsMeleeAttacking = false;
	}
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_BaseCharacter::DoMeleeAttack()
{
	const FVector MeleeAttackLocation = GetMesh()->GetSocketLocation(MeleeAttackBoneName);
	const TArray<AActor*> ActorsToIgnore = { this };
	TArray<AActor*> OutHitActors;

	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), MeleeAttackLocation, MeleeAttackRange, MeleeObjectTypes, AActor::StaticClass(), ActorsToIgnore, OutHitActors))
	{
		AActor* HitActor = OutHitActors[0];
		if (IsValid(HitActor))
		{
			USTS_HealthComponent* HitActorHealthComponent = Cast<USTS_HealthComponent>(HitActor->GetComponentByClass(USTS_HealthComponent::StaticClass()));
			if (IsValid(HitActorHealthComponent))
			{
				HitActorHealthComponent->Kill(GetController(), this);
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_BaseCharacter::StartFire()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StartFire();
	}
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_BaseCharacter::StopFire()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopFire();
	}
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	AttachWeaponToCharacter();

	if (IsValid(HealthComponent))
	{
		HealthComponent->OnHealthChanged.AddDynamic(this, &ASTS_BaseCharacter::OnHealthChanged);
		HealthComponent->OnDeath.AddDynamic(this, &ASTS_BaseCharacter::OnDeath);
	}

	AnimInstance = GetMesh()->GetAnimInstance();
	if (IsValid(AnimInstance))
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &ASTS_BaseCharacter::FinishMelee);
	}
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_BaseCharacter::AttachWeaponToCharacter()
{
	if (IsValid(StartingWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<ASTS_Weapon>(StartingWeaponClass);
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocketName);
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_BaseCharacter::OnHealthChanged(USTS_HealthComponent* HealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{

}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_BaseCharacter::OnDeath(USTS_HealthComponent* HealthComp, class AController* InstigatedBy, AActor* Killer)
{
	StopFire();
	GetMovementComponent()->StopMovementImmediately();
	SetActorEnableCollision(false);
}

