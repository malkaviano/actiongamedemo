// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

#include "AGD_CharacterAnimationData.generated.h"

USTRUCT(BlueprintType)
struct AGDEMONSTRATION_API FAGD_CharacterAnimationData {
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditDefaultsOnly)
    class UBlendSpace* LocomotionBlendSpace;

    UPROPERTY(EditDefaultsOnly)
    class UAnimSequenceBase* IdleAnimationAsset;
};
