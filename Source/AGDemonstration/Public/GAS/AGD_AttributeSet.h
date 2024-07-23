// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "AGD_AttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)                           \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)                 \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)                               \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)                               \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *
 */
UCLASS()
class AGDEMONSTRATION_API UAGD_AttributeSet : public UAttributeSet {
    GENERATED_BODY()

  public:
    UPROPERTY(BlueprintReadOnly, Category = "GAS",
              ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UAGD_AttributeSet, Health)

    UPROPERTY(BlueprintReadOnly, Category = "GAS",
              ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UAGD_AttributeSet, MaxHealth)

  public:
    virtual void GetLifetimeReplicatedProps(
        TArray<class FLifetimeProperty>& OutLifetimeProps) const;

    virtual void PostGameplayEffectExecute(
        const struct FGameplayEffectModCallbackData& Data) override;

  protected:
    UFUNCTION()
    virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
    virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
};
