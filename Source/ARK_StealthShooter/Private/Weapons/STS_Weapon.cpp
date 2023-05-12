// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/STS_Weapon.h"
#include "ARK_StealthShooter/ARK_StealthShooter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"

//--------------------------------------------------------------------------------------------------------------------
ASTS_Weapon::ASTS_Weapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = WeaponMesh;

	ShotDistance = 10000.f;
	ShotDamage = 20.f;
	RoundsPerMinute = 600.f;
	bDrawDebug = false;
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_Weapon::StartFire()
{
	float FirstShotDelay = FMath::Max(0.f, LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds);
	GetWorldTimerManager().SetTimer(TimerHandle_AutoFire, this, &ASTS_Weapon::Fire, TimeBetweenShots, true, FirstShotDelay);
}

//--------------------------------------------------------------------------------------------------------------------
void ASTS_Weapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_AutoFire);
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

		FVector ImpactPoint = TraceEnd;
		
		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, WEAPON_COLLISION, QueryParams))
		{
			AActor* HitActor = Hit.GetActor();
			UGameplayStatics::ApplyPointDamage(HitActor, ShotDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(), this, WeaponDamageType);

			ImpactPoint = Hit.ImpactPoint;

			if (IsValid(ImpactEffect))
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, ImpactPoint, Hit.ImpactNormal.Rotation());
			}
		}

		if (IsValid(MuzzleEffect))
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, WeaponMesh, MuzzleSocketName);
		}

		if (IsValid(TraceEffect))
		{
			UParticleSystemComponent* TraceComponent = UGameplayStatics::SpawnEmitterAttached(TraceEffect, WeaponMesh, MuzzleSocketName);
			if (IsValid(TraceComponent))
			{
				TraceComponent->SetVectorParameter(TraceTargetName, ImpactPoint);
			}
		}

		if (bDrawDebug)
		{
			DrawDebugLine(GetWorld(), EyeLocation, ImpactPoint, FColor::White, false, 1.f, 0, 1.f);
		}
	}

	LastFireTime = GetWorld()->TimeSeconds;
}

//--------------------------------------------------------------------------------------------------------------------s
void ASTS_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
	TimeBetweenShots = 60 / RoundsPerMinute;
}
