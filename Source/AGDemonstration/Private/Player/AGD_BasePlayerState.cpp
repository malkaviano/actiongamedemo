// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/AGD_BasePlayerState.h"

#include "AbilitySystemComponent.h"
#include "GAS/AGD_AbilitySystemComponent.h"
#include "GAS/AGD_AttributeSet.h"

AAGD_BasePlayerState::AAGD_BasePlayerState()
{
    NetUpdateFrequency = 100.f;

    NetPriority = 3.f;

    // GAS
    AbilitySystemComponent =
        CreateDefaultSubobject<UAGD_AbilitySystemComponent>(
            TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(
        EGameplayEffectReplicationMode::Mixed);

    AttributeSet = CreateDefaultSubobject<UAGD_AttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AAGD_BasePlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}