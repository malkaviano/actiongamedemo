// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Containers/Array.h"
#include "GameplayEffect.h"
#include "Templates/SubclassOf.h"
#include "UObject/ObjectMacros.h"

#include "AGD_CharacterData.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct AGDEMONSTRATION_API FAGD_CharacterData {
    GENERATED_USTRUCT_BODY();

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<TSubclassOf<class UGameplayEffect>> Effects;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<TSubclassOf<class UGameplayAbility>> Abilities;

	// GAS Actions
    UPROPERTY(EditDefaultsOnly)
    FGameplayTag JumpEventTag;

    UPROPERTY(EditDefaultsOnly)
    UInputAction* JumpAction;

    UPROPERTY(EditDefaultsOnly)
    FGameplayTag CrouchEventTag;

    UPROPERTY(EditDefaultsOnly)
    UInputAction* CrouchAction;

	// Native Actions
    UPROPERTY(EditDefaultsOnly)
    UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly)
    UInputAction* LookAction;
};
