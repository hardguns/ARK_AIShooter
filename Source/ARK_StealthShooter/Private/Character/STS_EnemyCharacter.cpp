// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/STS_EnemyCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

//--------------------------------------------------------------------------------------------------------------------
void ASTS_EnemyCharacter::SetEnemyStatus(ESTS_EnemyStatus NewEnemyStatus)
{
	const float Speed = EnemySpeedMap[NewEnemyStatus];
	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (IsValid(MovementComponent))
	{
		MovementComponent->MaxWalkSpeed = Speed;
	}
	
	BP_SetEnemyStatus(NewEnemyStatus);
}
