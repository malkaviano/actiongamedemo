// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"

#include "AGD_AssetManager.generated.h"

UCLASS()
class AGDEMONSTRATION_API UAGD_AssetManager : public UAssetManager {
    GENERATED_BODY()

  public:
    static UAGD_AssetManager& Get();

  protected:
    virtual void StartInitialLoading() override;
};
