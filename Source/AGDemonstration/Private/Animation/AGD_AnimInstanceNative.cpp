// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/AGD_AnimInstanceNative.h"

#include "Character/AGD_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/Object.h"

void UAGD_AnimInstanceNative::NativeInitializeAnimation()
{
    if ((OwningCharacter = Cast<AAGD_BaseCharacter>(TryGetPawnOwner()))) {
        CharacterMovementComponent = OwningCharacter->GetCharacterMovement();
    }
}

void UAGD_AnimInstanceNative::NativeThreadSafeUpdateAnimation(
    float DeltaSeconds)
{
    if (IsValid(OwningCharacter) && CharacterMovementComponent) {
        GroundSpeed = OwningCharacter->GetVelocity().Size2D();

        bHasGroundAcceleration =
            CharacterMovementComponent->GetCurrentAcceleration()
                .SizeSquared2D() > 0.f;        
    }
}
