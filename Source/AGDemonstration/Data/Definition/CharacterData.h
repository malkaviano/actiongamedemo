// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Containers/Array.h"
#include "GameplayEffect.h"
#include "Templates/SubclassOf.h"
#include "UObject/ObjectMacros.h"

#include "CharacterData.generated.h"

USTRUCT(BlueprintType)
struct AGDEMONSTRATION_API FCharacterData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayEffect>> Effects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbility>> Abilities;
};
