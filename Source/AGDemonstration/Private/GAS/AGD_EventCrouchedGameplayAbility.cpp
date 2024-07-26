// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AGD_EventCrouchedGameplayAbility.h"
#include "Manager/AGD_TagManager.h"

UAGD_EventCrouchedGameplayAbility::UAGD_EventCrouchedGameplayAbility() : Super()
{
    AbilityTags.AddTag(FAGD_TagManager::Get().Event_Ability_OnGround_Crouch);

    ActivationOwnedTags.AddTag(FAGD_TagManager::Get().State_OnGround_Crouching);
}

// void UAGD_EventCrouchedGameplayAbility::ActivateAbility(
//     const FGameplayAbilitySpecHandle Handle,
//     const FGameplayAbilityActorInfo* OwnerInfo,
//     const FGameplayAbilityActivationInfo ActivationInfo,
//     const FGameplayEventData* TriggerEventData)
// {
//     Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo,
//     TriggerEventData);

// UAbilityTask_WaitGameplayEvent* WaitGameplayEvent =
//     UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
//         this, FAGD_TagManager::Get().Event_Ability_OnGround_UnCrouch,
//         nullptr, true, true);

// WaitGameplayEvent->EventReceived.AddDynamic(
//     this, &UAGD_EventCrouchedGameplayAbility::Execute);
// }

// void UAGD_EventCrouchedGameplayAbility::Execute(FGameplayEventData Payload)
// {
//     CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(),
//                   GetCurrentActivationInfo(), true);
// }