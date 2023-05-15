// Fill out your copyright notice in the Description page of Project Settings.


#include "Patrol/STS_PatrolActor.h"
#include "Components/SplineComponent.h"

//--------------------------------------------------------------------------------------------------------------------
ASTS_PatrolActor::ASTS_PatrolActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PatrolSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("PatrolSplineComponent"));

}

//--------------------------------------------------------------------------------------------------------------------
FVector ASTS_PatrolActor::GetWorldLocationByIndex(const int32 Index) const
{
	if (IsValid(PatrolSplineComponent) && Index <= GetLastIndex())
	{
		return PatrolSplineComponent->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
	}

	return GetActorLocation();
}

//--------------------------------------------------------------------------------------------------------------------
int32 ASTS_PatrolActor::GetLastIndex() const
{
	if (IsValid(PatrolSplineComponent))
	{
		PatrolSplineComponent->GetNumberOfSplinePoints();
	}

	return INDEX_NONE;
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_PatrolActor::BeginPlay()
{
	Super::BeginPlay();
	
}


