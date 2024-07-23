// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AGD_BaseCharacter.h"

#include "AGD_PlayerCharacter.generated.h"

/**
 *
 */
UCLASS()
class AGDEMONSTRATION_API AAGD_PlayerCharacter : public AAGD_BaseCharacter {
    GENERATED_BODY()

  protected:
    virtual void PossessedBy(AController* NewController) override;

    virtual void OnRep_PlayerState() override;

    virtual void OnPlayerStateChanged(APlayerState* NewPlayerState,
                                      APlayerState* OldPlayerState) override;
};
