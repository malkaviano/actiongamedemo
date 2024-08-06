// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Definition/AGD_AnimationStanceData.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ObjectPtr.h"

#include "AGD_CharacterAnimationData.generated.h"

class UBlendSpace;
class UAnimSequenceBase;

USTRUCT(BlueprintType)
struct AGDEMONSTRATION_API FAGD_CharacterAnimationData {
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditDefaultsOnly)
    FAGD_AnimationStanceData UnarmedData;
};
