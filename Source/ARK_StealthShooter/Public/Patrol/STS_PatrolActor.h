// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STS_PatrolActor.generated.h"

class USplineComponent;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_PatrolActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ASTS_PatrolActor();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USplineComponent* PatrolSplineComponent;

	UFUNCTION(BlueprintCallable)
	FVector GetWorldLocationByIndex(const int32 Index) const;

	UFUNCTION(BlueprintCallable)
	int32 GetLastIndex() const;
		 
protected:

	virtual void BeginPlay() override;

};
