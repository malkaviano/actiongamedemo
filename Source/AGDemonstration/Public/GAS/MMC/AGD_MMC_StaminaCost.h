// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"

#include "AGD_MMC_StaminaCost.generated.h"

/**
 * 
 */
UCLASS()
class AGDEMONSTRATION_API UAGD_MMC_StaminaCost : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UAGD_MMC_StaminaCost();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;	
private:
	FGameplayEffectAttributeCaptureDefinition StaminaDef;
};
