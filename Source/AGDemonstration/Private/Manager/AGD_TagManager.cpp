// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager/AGD_TagManager.h"
#include "GameplayTagsManager.h"

FAGD_TagManager FAGD_TagManager::GameplayTags;

const FAGD_TagManager& FAGD_TagManager::Get() { return GameplayTags; }

void FAGD_TagManager::InitializeNativeGameplayTags()
{
    GameplayTags.Event_Ability_OnGround_Crouch =
        UGameplayTagsManager::Get().AddNativeGameplayTag(
            FName("Event.Ability.OnGround.Crouch"),
            FString("Event Signals Crouch"));

    GameplayTags.Event_Ability_OnGround_UnCrouch =
        UGameplayTagsManager::Get().AddNativeGameplayTag(
            FName("Event.Ability.OnGround.UnCrouch"),
            FString("Event Signals UnCrouch"));

    GameplayTags.Event_Ability_OnGround_Landed =
        UGameplayTagsManager::Get().AddNativeGameplayTag(
            FName("Event.Ability.OnGround.Landed"),
            FString("Event Signals Landed"));

    GameplayTags.Event_Ability_InAir_Jumped =
        UGameplayTagsManager::Get().AddNativeGameplayTag(
            FName("Event.Ability.InAir.Jumped"),
            FString("Event Signals Jumped"));

    GameplayTags.State_InAir_Jumped =
        UGameplayTagsManager::Get().AddNativeGameplayTag(
            FName("State.InAir.Jumped"), FString("State Signals State Jumped"));

    GameplayTags.State_OnGround_Crouching =
        UGameplayTagsManager::Get().AddNativeGameplayTag(
            FName("State.OnGround.Crouching"), FString("State Signals State Crouching"));
}