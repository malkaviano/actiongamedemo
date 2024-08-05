// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/Asset/AGD_CharacterDataAsset.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "Templates/SubclassOf.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ObjectPtr.h"

#include "AGD_BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class UAGD_AbilitySystemComponent;
class UAGD_AttributeSet;
class UAGD_EnhancedInputComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogBaseCharacter, Log, All);

UCLASS()
class AGDEMONSTRATION_API AAGD_BaseCharacter : public ACharacter,
                                               public IAbilitySystemInterface {
    GENERATED_BODY()

  public:
    // Sets default values for this character's properties
    AAGD_BaseCharacter();

    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const
    {
        return CameraBoom;
    }
    /** Returns FollowCamera subobject **/
    FORCEINLINE class UCameraComponent* GetFollowCamera() const
    {
        return FollowCamera;
    }

    UFUNCTION(BlueprintCallable, Category = "GAS")
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable, Category = "GAS")
    FActiveGameplayEffectHandle
    ApplyGEToSelf(TSubclassOf<class UGameplayEffect> Effect, float Level = 1.f);

    virtual void PostInitializeComponents() override;

    virtual void OnStartCrouch(float HalfHeightAdjust,
                               float ScaledHalfHeightAdjust) override;

    virtual void OnEndCrouch(float HalfHeightAdjust,
                             float ScaledHalfHeightAdjust) override;

    virtual void OnJumped_Implementation() override;

    virtual void Landed(const FHitResult& Hit) override;
  protected:
    UPROPERTY()
    TObjectPtr<UAGD_AbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY()
    TObjectPtr<UAGD_AttributeSet> AttributeSet;

    UPROPERTY(EditDefaultsOnly, Category = "Data Asset")
    TObjectPtr<UAGD_CharacterDataAsset> CharacterDataAsset;    

    // APawn interface
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

    virtual void PossessedBy(AController* NewController) override;

    virtual void GiveDAAbilities();

    virtual void ApplyDAEffects();

    UFUNCTION(BlueprintCallable)
    void SendGameplayEvent(FGameplayTag InputTagToggleOn, FGameplayTag InputTagToggleOff);

  private:
      /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;
    
    TMap<FGameplayTag, bool> ToggleState;

    float TriedToJump;

    FActiveGameplayEffectHandle JumpActiveHandle;

    void Move(const FInputActionValue& Value);
    
    void Look(const FInputActionValue& Value);

    void StartJump(const FInputActionValue& Value);

    void StopJump(const FInputActionValue& Value);

    void ToggleCrouch(const FInputActionValue& InputActionValue);

    void MaxMovementSpeedValueChanged(const FOnAttributeChangeData& Data);

    void SendGameplayEvent(FGameplayTag InputTag);
};
