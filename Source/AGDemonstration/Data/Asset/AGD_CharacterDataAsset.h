// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Definition/AGD_CharacterData.h"
#include "Engine/DataAsset.h"
#include "UObject/ObjectMacros.h"

#include "AGD_CharacterDataAsset.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class AGDEMONSTRATION_API UAGD_CharacterDataAsset : public UDataAsset {
    GENERATED_BODY()

  public:
    UPROPERTY(EditDefaultsOnly)
    FAGD_CharacterData CharacterData;
};
