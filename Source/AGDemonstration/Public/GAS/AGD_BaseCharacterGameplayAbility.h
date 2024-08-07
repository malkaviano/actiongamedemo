// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/AGD_BaseGameplayAbility.h"

#include "AGD_BaseCharacterGameplayAbility.generated.h"

class AAGD_BaseCharacter;

UCLASS()
class AGDEMONSTRATION_API UAGD_BaseCharacterGameplayAbility
    : public UAGD_BaseGameplayAbility {
    GENERATED_BODY()

  public:
	UAGD_BaseCharacterGameplayAbility();
	
    virtual void
    ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                    const FGameplayAbilityActorInfo* OwnerInfo,
                    const FGameplayAbilityActivationInfo ActivationInfo,
                    const FGameplayEventData* TriggerEventData) override;

  protected:
    UPROPERTY(BlueprintReadOnly, Category = "GAS")
    TObjectPtr<AAGD_BaseCharacter> Character;
};
