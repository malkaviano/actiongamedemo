// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct AGDEMONSTRATION_API FAGD_TagManager {
  public:
    static const FAGD_TagManager& Get();

    static void InitializeNativeGameplayTags();

    /***
      Events
    */
    FGameplayTag Event_Ability_OnGround_Crouch;
    FGameplayTag Event_Ability_OnGround_UnCrouch;
    FGameplayTag Event_Ability_OnGround_Landed;

    FGameplayTag Event_Ability_InAir_Jumped;

    /***
      States
    */
    FGameplayTag State_InAir_Jumped;

    FGameplayTag State_OnGround_Crouching;

  private:
    static FAGD_TagManager GameplayTags;
};
