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
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAGD_AbilitySystemComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogBaseCharacter, Log, All);

UCLASS(config = Game)
class AGDEMONSTRATION_API AAGD_BaseCharacter : public ACharacter,
                                               public IAbilitySystemInterface {
    GENERATED_BODY()

  public:
    // Sets default values for this character's properties
    AAGD_BaseCharacter();

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;

    /** MappingContext */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    /** Jump Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    /** Look Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction* LookAction;

    /** Crouch Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction* CrouchAction;

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

    virtual void
    OnStartCrouch(float HalfHeightAdjust,
                                      float ScaledHalfHeightAdjust) override;

    virtual void OnEndCrouch(float HalfHeightAdjust,
                             float ScaledHalfHeightAdjust) override;

  protected:
    UPROPERTY()
    TObjectPtr<UAGD_AbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Data Asset")
    TObjectPtr<UAGD_CharacterDataAsset> CharacterDataAsset;

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Jump")
    FGameplayTag JumpEventTag;

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Crouch")
    FGameplayTag CrouchEventTag;

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Crouch")
    FGameplayTag UnCrouchEventTag;

    // APawn interface
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

    // To add mapping context
    virtual void BeginPlay() override;

    virtual void PossessedBy(AController* NewController) override;

    virtual void GiveDAAbilities();

    virtual void ApplyDAEffects();

  private:
    /** Called for movement input */
    void Move(const FInputActionValue& Value);

    /** Called for looking input */
    void Look(const FInputActionValue& Value);

    void OnJumpStarted(const FInputActionValue& Value);

    void OnJumpEnded(const FInputActionValue& Value);

    void OnCrouch(const FInputActionValue& Value);
};
