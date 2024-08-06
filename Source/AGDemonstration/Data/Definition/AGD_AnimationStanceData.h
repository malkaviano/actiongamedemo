// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

#include "AGD_AnimationStanceData.generated.h"

class UBlendSpace;
class UAnimSequenceBase;


USTRUCT(BlueprintType)
struct AGDEMONSTRATION_API FAGD_AnimationStanceData {
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UBlendSpace> BlendSpace;

    UPROPERTY(EditDefaultsOnly)
    TArray<TObjectPtr<UAnimSequenceBase>> IdleAnimationAssets;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UBlendSpace> CrouchedBlendSpace;

    UPROPERTY(EditDefaultsOnly)
    TArray<TObjectPtr<UAnimSequenceBase>> CrouchedIdleAnimationAssets;
};
