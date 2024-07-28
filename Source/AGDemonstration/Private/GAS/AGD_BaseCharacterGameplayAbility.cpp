// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AGD_BaseCharacterGameplayAbility.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Character/AGD_BaseCharacter.h"

UAGD_BaseCharacterGameplayAbility::UAGD_BaseCharacterGameplayAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UAGD_BaseCharacterGameplayAbility::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* OwnerInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Character = Cast<AAGD_BaseCharacter>(OwnerInfo->OwnerActor.Get());

    if (IsValid(Character)) {
        Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo,
                               TriggerEventData);
    }
    else {
        EndAbility(Handle, OwnerInfo, ActivationInfo, true, false);
    }
}