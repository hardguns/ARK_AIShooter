// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/STS_EnvQueryHealAreaStatus.h"
#include "Internationalization/Text.h"
#include "Interactable/STS_HealingArea.h"

//--------------------------------------------------------------------------------------------------------------------
USTS_EnvQueryHealAreaStatus::USTS_EnvQueryHealAreaStatus(const FObjectInitializer& ObjectInitializer)
{

}

//--------------------------------------------------------------------------------------------------------------------
void USTS_EnvQueryHealAreaStatus::RunTest(FEnvQueryInstance& QueryInstance) const
{
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		ASTS_HealingArea* HealingArea = Cast<ASTS_HealingArea>(GetItemActor(QueryInstance, It.GetIndex()));
		float Score = 0.f;
		if (IsValid(HealingArea))
		{
			Score = HealingArea->bIsActive ? 1.f : 0.f;
			It.SetScore(TestPurpose, FilterType, Score, 0.f, 1.f);

			It.ForceItemState(HealingArea->bIsActive ? EEnvItemStatus::Passed : EEnvItemStatus::Failed);
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------
FText USTS_EnvQueryHealAreaStatus::GetDescriptionTitle() const
{
	const FString& DescriptionTitle = "Testing for Healing area status";
	return FText().FromString(DescriptionTitle);
}

//--------------------------------------------------------------------------------------------------------------------
FText USTS_EnvQueryHealAreaStatus::GetDescriptionDetails() const
{
	const FString& DescriptionTitle = "Score when active : 1, Score when inactive : 0";
	return FText().FromString(DescriptionTitle);
}
