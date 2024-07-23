// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/Asset/AGD_CharacterAnimDataAsset.h"
#include "UObject/ObjectMacros.h"

#include "AGD_AnimInstance.generated.h"

/**
 *
 */
UCLASS()
class AGDEMONSTRATION_API UAGD_AnimInstance : public UAnimInstance {
    GENERATED_BODY()

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Data Asset")
    TObjectPtr<UAGD_CharacterAnimDataAsset> CharacterAnimDataAsset;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	class UBlendSpace* GetLocomotionBlendSpace() const;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	class UAnimSequenceBase* GetIdleAnimation() const;
};
