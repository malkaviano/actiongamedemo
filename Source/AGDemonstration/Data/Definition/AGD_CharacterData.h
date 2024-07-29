// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Containers/Array.h"
#include "GameplayEffect.h"
#include "Templates/SubclassOf.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ObjectPtr.h"
#include "Data/Definition/AGD_GameplayAbilityInput.h"

#include "AGD_CharacterData.generated.h"

USTRUCT(BlueprintType)
struct AGDEMONSTRATION_API FAGD_CharacterData {
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditDefaultsOnly)
    TArray<TSubclassOf<UGameplayEffect>> Effects;

    UPROPERTY(EditDefaultsOnly)
    TArray<TSubclassOf<UGameplayAbility>> Abilities;

    UPROPERTY(EditDefaultsOnly)
    TArray<FAGD_GameplayAbilityInput> GameplayInputActions;

    // Native Actions
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> LookAction;
};
