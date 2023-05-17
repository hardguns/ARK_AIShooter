// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/STS_HealingArea.h"
#include "Components/StaticMeshComponent.h"
#include "Character/STS_BaseCharacter.h"
#include "Components/STS_HealthComponent.h"

//--------------------------------------------------------------------------------------------------------------------
ASTS_HealingArea::ASTS_HealingArea()
{
	PrimaryActorTick.bCanEverTick = false;

	AreaMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AreaMeshComponent"));
	SetRootComponent(AreaMeshComponent);

	bIsActive = true;
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_HealingArea::Heal(ASTS_BaseCharacter* HealCharacter)
{
	if (!IsValid(HealCharacter))
	{
		return;
	}

	USTS_HealthComponent* HealthComponent = HealCharacter->GetHealthComponent();
	if (IsValid(HealthComponent))
	{
		HealthComponent->Heal(HealingAmount, nullptr, this);
	}

	bIsActive = false;
	AreaMeshComponent->SetVisibility(false);
	AreaMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorldTimerManager().SetTimer(TimerHandle_Cooldown, this, &ASTS_HealingArea::Reset, CooldownTime, false);
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_HealingArea::Reset()
{
	bIsActive = true;
	AreaMeshComponent->SetVisibility(true);
	AreaMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_HealingArea::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AreaMeshComponent))
	{
		AreaMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASTS_HealingArea::OnOverlap);
	}
	
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_HealingArea::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASTS_BaseCharacter* OverlappingCharacter = Cast<ASTS_BaseCharacter>(OtherActor))
	{
		Heal(OverlappingCharacter);
	}
}

