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

UBlendSpace* UAGD_AnimInstance::GetCrouchBlendSpace() const {
    return CharacterAnimDataAsset->CharacterAnimationData.CrouchBlendSpace;
}

UAnimSequenceBase* UAGD_AnimInstance::GetCrouchIdleAnimation() const {
    return CharacterAnimDataAsset->CharacterAnimationData.CrouchAnimationAsset;
}