// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/AGD_AttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"

#include "AGD_BasePlayerState.generated.h"

class UAbilitySystemComponent;
class UAGD_AbilitySystemComponent;

/**
 *
 */
UCLASS()
class AGDEMONSTRATION_API AAGD_BasePlayerState : public APlayerState {
    GENERATED_BODY()

  public:
    AAGD_BasePlayerState();
};
