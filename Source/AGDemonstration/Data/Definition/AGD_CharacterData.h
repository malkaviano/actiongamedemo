// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Array.h"
#include "Data/Definition/AGD_CharacterActionSet.h"
#include "Data/Definition/AGD_CharacterConfigValues.h"
#include "Templates/SubclassOf.h"
#include "UObject/ObjectMacros.h"

#include "AGD_CharacterData.generated.h"

class UInputMappingContext;
class UGameplayEffect;
class UGameplayAbility;
struct FAGD_GameplayAbilityInput;
class UInputAction;

USTRUCT(BlueprintType)
struct AGDEMONSTRATION_API FAGD_CharacterData {
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditDefaultsOnly)
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly)
    TArray<TSubclassOf<UGameplayEffect>> Effects;

    UPROPERTY(EditDefaultsOnly)
    TArray<TSubclassOf<UGameplayAbility>> Abilities;

    UPROPERTY(EditDefaultsOnly)
    TArray<FAGD_GameplayAbilityInput> GameplayInputActions;

    /// Native Actions
    UPROPERTY(EditDefaultsOnly)
    FAGD_CharacterActionSet ActionSet;

    UPROPERTY(EditDefaultsOnly)
    FAGD_CharacterConfigValues ConfigValues;
};
