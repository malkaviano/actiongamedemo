// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AGD_AttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Math/UnrealMathUtility.h"
#include "Net/UnrealNetwork.h"

void UAGD_AttributeSet::PostGameplayEffectExecute(
    const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    }

    if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute()) {
        SetMaxHealth(FMath::Max(0.f, GetMaxHealth()));
    }
}

void UAGD_AttributeSet::GetLifetimeReplicatedProps(
    TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UAGD_AttributeSet, Health, COND_None,
                                   REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAGD_AttributeSet, MaxHealth, COND_None,
                                   REPNOTIFY_Always);
}

void UAGD_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAGD_AttributeSet, Health, OldHealth);
}

void UAGD_AttributeSet::OnRep_MaxHealth(
    const FGameplayAttributeData& OldMaxHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAGD_AttributeSet, MaxHealth, OldMaxHealth);
}