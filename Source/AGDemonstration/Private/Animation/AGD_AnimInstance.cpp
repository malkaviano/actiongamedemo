// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/AGD_AnimInstance.h"
#include "Animation/AnimationAsset.h"

UBlendSpace* UAGD_AnimInstance::GetUnarmedBlendSpace() const
{
    return CharacterAnimDataAsset->CharacterAnimationData.UnarmedData
        .BlendSpace;
}

UAnimSequenceBase*
UAGD_AnimInstance::GetUnarmedIdleAnimation(const int32 Index) const
{
    return CharacterAnimDataAsset->CharacterAnimationData.UnarmedData
        .IdleAnimationAssets[Index];
}

UBlendSpace* UAGD_AnimInstance::GetUnarmedCrouchBlendSpace() const
{
    return CharacterAnimDataAsset->CharacterAnimationData.UnarmedData
        .CrouchedBlendSpace;
}

UAnimSequenceBase*
UAGD_AnimInstance::GetUnarmedCrouchIdleAnimation(const int32 Index) const
{
    return CharacterAnimDataAsset->CharacterAnimationData.UnarmedData
        .CrouchedIdleAnimationAssets[Index];
}

UBlendSpace* UAGD_AnimInstance::GetUnarmedSprintBlendSpace() const {
     return CharacterAnimDataAsset->CharacterAnimationData.UnarmedData
        .SprintBlendSpace;
}