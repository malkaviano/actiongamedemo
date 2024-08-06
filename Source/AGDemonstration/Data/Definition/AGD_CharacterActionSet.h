// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AGD_CharacterActionSet.generated.h"

class UGameplayEffect;
class UGameplayAbility;
struct FAGD_GameplayAbilityInput;
class UInputAction;

USTRUCT(BlueprintType)
struct AGDEMONSTRATION_API FAGD_CharacterActionSet
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> CrouchAction;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> JumpAction;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UGameplayEffect> JumpEffect;
};
