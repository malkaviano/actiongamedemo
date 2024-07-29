// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Definition/AGD_CharacterAnimationData.h"
#include "Engine/DataAsset.h"

#include "AGD_CharacterAnimDataAsset.generated.h"

UCLASS(BlueprintType)
class AGDEMONSTRATION_API UAGD_CharacterAnimDataAsset : public UDataAsset {
    GENERATED_BODY()

  public:
    UPROPERTY(EditDefaultsOnly)
    FAGD_CharacterAnimationData CharacterAnimationData;
};
