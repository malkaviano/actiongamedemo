// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/MMC/AGD_MMC_StaminaCost.h"

#include "GAS/AGD_AttributeSet.h"
#include "GAS/AGD_BaseCharacterGameplayAbility.h"
#include "GameplayEffectAttributeCaptureDefinition.h"

UAGD_MMC_StaminaCost::UAGD_MMC_StaminaCost()
{
    StaminaDef.AttributeToCapture = UAGD_AttributeSet::GetStaminaAttribute();
    StaminaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
    StaminaDef.bSnapshot = true;

    RelevantAttributesToCapture.Add(StaminaDef);
}

float UAGD_MMC_StaminaCost::CalculateBaseMagnitude_Implementation(
    const FGameplayEffectSpec& Spec) const
{
    const UAGD_BaseCharacterGameplayAbility* Ability =
        Cast<UAGD_BaseCharacterGameplayAbility>(
            Spec.GetContext().GetAbilityInstance_NotReplicated());

    return Ability ? Ability->GetCost() : 0.f;
}