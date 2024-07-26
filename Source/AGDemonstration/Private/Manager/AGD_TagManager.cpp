// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager/AGD_TagManager.h"
#include "GameplayTagsManager.h"

FAGD_TagManager FAGD_TagManager::GameplayTags;

const FAGD_TagManager& FAGD_TagManager::Get() { return GameplayTags; }

void FAGD_TagManager::InitializeNativeGameplayTags()
{
    GameplayTags.Event_Ability_OnGround_UnCrouch =
        UGameplayTagsManager::Get().AddNativeGameplayTag(
            FName("Event.Ability.OnGround.UnCrouch"),
            FString("Event Signals UnCrouch"));
}