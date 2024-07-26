// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager/AGD_AssetManager.h"

#include "Manager/AGD_TagManager.h"
#include "AbilitySystemGlobals.h"

UAGD_AssetManager& UAGD_AssetManager::Get()
{
    check(GEngine);

    UAGD_AssetManager* AGD_AssetManager =
        Cast<UAGD_AssetManager>(GEngine->AssetManager);

    return *AGD_AssetManager;
}

void UAGD_AssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();

    FAGD_TagManager::InitializeNativeGameplayTags();

    UAbilitySystemGlobals::Get().InitGlobalData();
}