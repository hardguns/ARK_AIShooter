// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/STS_BaseCharacter.h"
#include "STS_EnemyCharacter.generated.h"

class ASTS_PatrolActor;

/**
 * 
 */
UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_EnemyCharacter : public ASTS_BaseCharacter
{
	GENERATED_BODY()

public: 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	ASTS_PatrolActor* PatrolActorReference;
	
};
