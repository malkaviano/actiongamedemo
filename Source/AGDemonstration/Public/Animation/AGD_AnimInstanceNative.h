// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Animation/AGD_AnimInstance.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ObjectPtr.h"

#include "AGD_AnimInstanceNative.generated.h"

class AAGD_BaseCharacter;
class UCharacterMovementComponent;

UCLASS()
class AGDEMONSTRATION_API UAGD_AnimInstanceNative : public UAGD_AnimInstance {
    GENERATED_BODY()

  public:
    virtual void NativeInitializeAnimation() override;

    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

  protected:
    UPROPERTY()
    TObjectPtr<AAGD_BaseCharacter> OwningCharacter;

    UPROPERTY()
    TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OwningCharacter|Locomotion")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OwningCharacter|Locomotion")
	bool bHasGroundAcceleration;
};
