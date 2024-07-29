// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"

#include "AGD_GameplayAbilityInput.generated.h"

USTRUCT(BlueprintType) struct AGDEMONSTRATION_API FAGD_GameplayAbilityInput {
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditDefaultsOnly)
    FGameplayTag TriggeredTag;

    UPROPERTY(EditDefaultsOnly)
    FGameplayTag StartedTag;

    UPROPERTY(EditDefaultsOnly)
    FGameplayTag OngoingTag;

    UPROPERTY(EditDefaultsOnly)
    FGameplayTag CanceledTag;

    UPROPERTY(EditDefaultsOnly)
    FGameplayTag CompletedTag;

    UPROPERTY(EditDefaultsOnly)
    FGameplayTag ToggleOnTag;

    UPROPERTY(EditDefaultsOnly)
    FGameplayTag ToggleOffTag;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> InputAction;

    FAGD_GameplayAbilityInput()
    {
        TriggeredTag = FGameplayTag();
        StartedTag = FGameplayTag();
        OngoingTag = FGameplayTag();
        CanceledTag = FGameplayTag();
        CompletedTag = FGameplayTag();

        ToggleOnTag = FGameplayTag();
        ToggleOffTag = FGameplayTag();

        InputAction = nullptr;
    }
};
