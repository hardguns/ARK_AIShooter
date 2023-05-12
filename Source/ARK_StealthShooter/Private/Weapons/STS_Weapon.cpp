// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/STS_Weapon.h"
#include "ARK_StealthShooter/ARK_StealthShooter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

//--------------------------------------------------------------------------------------------------------------------
ASTS_Weapon::ASTS_Weapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = WeaponMesh;

	ShotDistance = 10000.f;
	ShotDamage = 20.f;
}

void ASTS_Weapon::Fire()
{
	AActor* MyOwner = GetOwner();
	if (IsValid(MyOwner))
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * ShotDistance);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;
		
		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, WEAPON_COLLISION, QueryParams))
		{
			AActor* HitActor = Hit.GetActor();
			UGameplayStatics::ApplyPointDamage(HitActor, ShotDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(), this, WeaponDamageType);

			DrawDebugLine(GetWorld(), EyeLocation, Hit.ImpactPoint, FColor::White, false, 1.f, 0, 1.f);
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------s
void ASTS_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}
