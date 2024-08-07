// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "AGD_BaseGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EGAActivationPolicy : uint8 { OnTriggered, OnGiven };

UCLASS()
class AGDEMONSTRATION_API UAGD_BaseGameplayAbility : public UGameplayAbility {
    GENERATED_BODY()

  public:
    UAGD_BaseGameplayAbility();
    
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

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Activation Policy")
    EGAActivationPolicy AbilityActivationPolicy;

    virtual void ApplyEffects(UAbilitySystemComponent* AbilitySystemComponent);

    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
                            const FGameplayAbilityActorInfo* ActorInfo,
                            const FGameplayAbilityActivationInfo ActivationInfo,
                            bool bReplicateEndAbility,
                            bool bWasCancelled) override;

    virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilitySpec& Spec);

  private:
    TArray<FActiveGameplayEffectHandle> ActiveEffects;
};
