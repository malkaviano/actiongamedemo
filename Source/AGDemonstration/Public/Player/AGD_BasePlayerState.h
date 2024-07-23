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
class AGDEMONSTRATION_API AAGD_BasePlayerState
    : public APlayerState,
      public IAbilitySystemInterface {
    GENERATED_BODY()

  public:
    AAGD_BasePlayerState();

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

  protected:
    UPROPERTY()
    TObjectPtr<UAGD_AbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY()
    TObjectPtr<UAGD_AttributeSet> AttributeSet;
};
