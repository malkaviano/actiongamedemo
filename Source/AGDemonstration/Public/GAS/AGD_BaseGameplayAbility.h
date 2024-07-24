// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "AGD_BaseGameplayAbility.generated.h"

UCLASS()
class AGDEMONSTRATION_API UAGD_BaseGameplayAbility : public UGameplayAbility {
    GENERATED_BODY()

  public:
    virtual void
    ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                    const FGameplayAbilityActorInfo* OwnerInfo,
                    const FGameplayAbilityActivationInfo ActivationInfo,
                    const FGameplayEventData* TriggerEventData) override;

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "GAS|Effects")
    TArray<TSubclassOf<UGameplayEffect>> AbilityEffects;

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Level")
    int32 AbilityLevel;

    virtual void ApplyEffects(UAbilitySystemComponent* AbilitySystemComponent);    

    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
                            const FGameplayAbilityActorInfo* ActorInfo,
                            const FGameplayAbilityActivationInfo ActivationInfo,
                            bool bReplicateEndAbility,
                            bool bWasCancelled) override;

  private:
    TArray<FActiveGameplayEffectHandle> ActiveEffects;
};
