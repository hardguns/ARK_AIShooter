// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/STS_BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Weapons/STS_Weapon.h"

//--------------------------------------------------------------------------------------------------------------------
ASTS_BaseCharacter::ASTS_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_BaseCharacter::StartFire()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->Fire();
	}
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	AttachWeaponToCharacter();
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

