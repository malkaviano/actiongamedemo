// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AGD_PlayerCharacter.h"

#include "Player/AGD_BasePlayerState.h"
#include "GAS/AGD_AbilitySystemComponent.h"

void AAGD_PlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
}

void AAGD_PlayerCharacter::OnRep_PlayerState() { Super::OnRep_PlayerState(); }

void AAGD_PlayerCharacter::OnPlayerStateChanged(APlayerState* NewPlayerState,
                                                APlayerState* OldPlayerState)
{
    Super::OnPlayerStateChanged(NewPlayerState, OldPlayerState);
}