// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AGD_AbilitySystemComponent.h"

FActiveGameplayEffectHandle
UAGD_AbilitySystemComponent::ApplyGEToSelf(
    TSubclassOf<UGameplayEffect> Effect, float Level)
{
    FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext();

    EffectContextHandle.AddSourceObject(this);

    FGameplayEffectSpecHandle SpecHandle =
        MakeOutgoingSpec(Effect, Level, EffectContextHandle);

    if (SpecHandle.IsValid()) {
        FActiveGameplayEffectHandle ActiveGEHandle =
            ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

        return ActiveGEHandle;
    }

    return FActiveGameplayEffectHandle();
}