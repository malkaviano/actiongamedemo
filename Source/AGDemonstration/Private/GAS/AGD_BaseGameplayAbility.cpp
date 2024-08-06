// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AGD_BaseGameplayAbility.h"

#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemComponent.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpec.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "Logging/LogVerbosity.h"
#include "Logging/StructuredLog.h"
#include "UObject/Field.h"

UAGD_BaseGameplayAbility::UAGD_BaseGameplayAbility()
{
    AbilityActivationPolicy = EGAActivationPolicy::OnTriggered;

    AbilityLevel = 1;
}

void UAGD_BaseGameplayAbility::ApplyEffects(
    UAbilitySystemComponent* AbilitySystemComponent)
{
    if (AbilitySystemComponent) {
        FGameplayEffectContextHandle EffectContextHandle =
            AbilitySystemComponent->MakeEffectContext();

        for (const auto& Effect : AbilityEffects) {
            FGameplayEffectSpecHandle EffectSpecHandle =
                AbilitySystemComponent->MakeOutgoingSpec(Effect, AbilityLevel,
                                                         EffectContextHandle);

            if (EffectSpecHandle.IsValid()) {
                FActiveGameplayEffectHandle ActiveGEHandle =
                    AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(
                        *EffectSpecHandle.Data);

                if (ActiveGEHandle.IsValid()) {
                    ActiveEffects.Add(ActiveGEHandle);
                }
                else {
                    UE_LOGFMT(LogTemp, Error,
                              "Failed to apply jump effect: {0}",
                              GetNameSafe(Effect));
                }
            }
        }
    }
}

void UAGD_BaseGameplayAbility::EndAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility, bool bWasCancelled)
{
    if (UAbilitySystemComponent* AbilitySystemComponent =
            ActorInfo->AbilitySystemComponent.Get()) {
        for (const auto& ActiveEffect : ActiveEffects) {
            if (ActiveEffect.IsValid()) {
                AbilitySystemComponent->RemoveActiveGameplayEffect(
                    ActiveEffect);
            }
        }

        ActiveEffects.Empty();
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility,
                      bWasCancelled);

    if (AbilityActivationPolicy == EGAActivationPolicy::OnGiven) {
        ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
    }
}

void UAGD_BaseGameplayAbility::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{

    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo) &&
        CommitAbility(Handle, ActorInfo, ActivationInfo)) {

        ApplyEffects(ActorInfo->AbilitySystemComponent.Get());

        Super::ActivateAbility(Handle, ActorInfo, ActivationInfo,
                               TriggerEventData);
    }
}

void UAGD_BaseGameplayAbility::OnGiveAbility(
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(ActorInfo, Spec);

    if (AbilityActivationPolicy == EGAActivationPolicy::OnGiven) {
        ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
    }
}