// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AGD_AbilitySystemComponent.generated.h"

/**
 *
 */
UCLASS()
class AGDEMONSTRATION_API UAGD_AbilitySystemComponent
    : public UAbilitySystemComponent {
    GENERATED_BODY()

  public:
    FActiveGameplayEffectHandle
    ApplyGEToSelf(TSubclassOf<class UGameplayEffect> Effect,
                              float Level);
};
