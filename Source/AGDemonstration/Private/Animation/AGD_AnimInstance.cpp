// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/AGD_AnimInstance.h"
#include "Animation/AnimationAsset.h"

UBlendSpace* UAGD_AnimInstance::GetLocomotionBlendSpace() const
{
    return CharacterAnimDataAsset->CharacterAnimationData.LocomotionBlendSpace;
}

UAnimSequenceBase* UAGD_AnimInstance::GetIdleAnimation() const
{
    return CharacterAnimDataAsset->CharacterAnimationData.IdleAnimationAsset;
}