// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AGD_BaseCharacter.h"

#include "Abilities/GameplayAbilityTargetTypes.h"
#include "ActiveGameplayEffectHandle.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/AGD_AttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "TimerManager.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "InputTriggers.h"
#include "Misc/AssertionMacros.h"
#include "Templates/Casts.h"
#include "GAS/AGD_AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Templates/SubclassOf.h"
#include "Logging/LogVerbosity.h"
#include "Logging/StructuredLog.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Core/AGD_NativeGameplayTags.h"
#include "Data/Definition/AGD_GameplayAbilityInput.h"

DEFINE_LOG_CATEGORY(LogBaseCharacter);

// Sets default values
AAGD_BaseCharacter::AAGD_BaseCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;

    GetMesh()->bReceivesDecals = false;

    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don't rotate when the controller rotates. Let that just affect the
    // camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement =
        true; // Character moves in the direction of input...
    GetCharacterMovement()->RotationRate =
        FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

    // Note: For faster iteration times these variables, and many more, can be
    // tweaked in the Character Blueprint instead of recompiling to adjust them
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    // Create a camera boom (pulls in towards the player if there is a
    // collision)
    CameraBoom =
        CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength =
        400.0f; // The camera follows at this distance behind the character
    CameraBoom->bUsePawnControlRotation =
        true; // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera =
        CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(
        CameraBoom,
        USpringArmComponent::SocketName); // Attach the camera to the end of the
                                          // boom and let the boom adjust to
                                          // match the controller orientation
    FollowCamera->bUsePawnControlRotation =
        false; // Camera does not rotate relative to arm

    // GAS
    AbilitySystemComponent =
        CreateDefaultSubobject<UAGD_AbilitySystemComponent>(
            TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(
        EGameplayEffectReplicationMode::Mixed);

    AttributeSet =
        CreateDefaultSubobject<UAGD_AttributeSet>(TEXT("AttributeSet"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAGD_BaseCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    // Add Input Mapping Context
    if (APlayerController* PlayerController =
            Cast<APlayerController>(GetController())) {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                    PlayerController->GetLocalPlayer())) {
            Subsystem->AddMappingContext(
                CharacterDataAsset->CharacterData.DefaultMappingContext, 0);
        }
    }

    // Set up action bindings
    if (UEnhancedInputComponent* EnhancedInputComponent =
            Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

        // Moving
        EnhancedInputComponent->BindAction(
            CharacterDataAsset->CharacterData.MoveAction,
            ETriggerEvent::Triggered, this, &AAGD_BaseCharacter::Move);

        // Looking
        EnhancedInputComponent->BindAction(
            CharacterDataAsset->CharacterData.LookAction,
            ETriggerEvent::Triggered, this, &AAGD_BaseCharacter::Look);

        // Jumping
        EnhancedInputComponent->BindAction(
            CharacterDataAsset->CharacterData.JumpAction,
            ETriggerEvent::Started, this, &AAGD_BaseCharacter::StartJump);

        EnhancedInputComponent->BindAction(
            CharacterDataAsset->CharacterData.JumpAction,
            ETriggerEvent::Completed, this, &AAGD_BaseCharacter::StopJump);

        // Crouching
        EnhancedInputComponent->BindAction(
            CharacterDataAsset->CharacterData.CrouchAction,
            ETriggerEvent::Started, this, &AAGD_BaseCharacter::ToggleCrouch);

        for (const FAGD_GameplayAbilityInput& AbilityInput :
             CharacterDataAsset->CharacterData.GameplayInputActions) {
            if (AbilityInput.TriggeredTag.IsValid()) {
                EnhancedInputComponent->BindAction(
                    AbilityInput.InputAction, ETriggerEvent::Triggered, this,
                    &AAGD_BaseCharacter::SendGameplayEvent,
                    AbilityInput.TriggeredTag);
            }

            if (AbilityInput.StartedTag.IsValid()) {
                EnhancedInputComponent->BindAction(
                    AbilityInput.InputAction, ETriggerEvent::Started, this,
                    &AAGD_BaseCharacter::SendGameplayEvent,
                    AbilityInput.StartedTag);
            }

            if (AbilityInput.OngoingTag.IsValid()) {
                EnhancedInputComponent->BindAction(
                    AbilityInput.InputAction, ETriggerEvent::Ongoing, this,
                    &AAGD_BaseCharacter::SendGameplayEvent,
                    AbilityInput.OngoingTag);
            }

            if (AbilityInput.CanceledTag.IsValid()) {
                EnhancedInputComponent->BindAction(
                    AbilityInput.InputAction, ETriggerEvent::Canceled, this,
                    &AAGD_BaseCharacter::SendGameplayEvent,
                    AbilityInput.CanceledTag);
            }

            if (AbilityInput.CompletedTag.IsValid()) {
                EnhancedInputComponent->BindAction(
                    AbilityInput.InputAction, ETriggerEvent::Completed, this,
                    &AAGD_BaseCharacter::SendGameplayEvent,
                    AbilityInput.CompletedTag);
            }

            if (AbilityInput.ToggleOnTag.IsValid() &&
                AbilityInput.ToggleOffTag.IsValid()) {
                EnhancedInputComponent->BindAction(
                    AbilityInput.InputAction, ETriggerEvent::Started, this,
                    &AAGD_BaseCharacter::SendGameplayEvent,
                    AbilityInput.ToggleOnTag, AbilityInput.ToggleOffTag);
            }
        }
    }
    else {
        UE_LOG(LogBaseCharacter, Error,
               TEXT("'%s' Failed to find an Enhanced Input component! This "
                    "template is built to use the Enhanced Input system. If "
                    "you intend to use the legacy system, then you will need "
                    "to update this C++ file."),
               *GetNameSafe(this));
    }
}

void AAGD_BaseCharacter::Move(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr) {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector ForwardDirection =
            FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // get right vector
        const FVector RightDirection =
            FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // add movement
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AAGD_BaseCharacter::Look(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr) {
        // add yaw and pitch input to controller
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AAGD_BaseCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    check(CharacterDataAsset);

    AbilitySystemComponent->InitAbilityActorInfo(this, this);

    GiveDAAbilities();
    ApplyDAEffects();

    AbilitySystemComponent
        ->GetGameplayAttributeValueChangeDelegate(
            AttributeSet->GetMaxMovementSpeedAttribute())
        .AddUObject(this, &AAGD_BaseCharacter::MaxMovementSpeedValueChanged);
}

UAbilitySystemComponent* AAGD_BaseCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

FActiveGameplayEffectHandle
AAGD_BaseCharacter::ApplyGEToSelf(TSubclassOf<UGameplayEffect> Effect,
                                  float Level)
{
    return AbilitySystemComponent->ApplyGEToSelf(Effect, Level);
}

void AAGD_BaseCharacter::GiveDAAbilities()
{
    for (auto Ability : CharacterDataAsset->CharacterData.Abilities) {
        AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability));
    }
}

void AAGD_BaseCharacter::ApplyDAEffects()
{
    for (auto Effect : CharacterDataAsset->CharacterData.Effects) {
        ApplyGEToSelf(Effect);
    }
}

void AAGD_BaseCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

void AAGD_BaseCharacter::OnStartCrouch(float HalfHeightAdjust,
                                       float ScaledHalfHeightAdjust)
{
    AbilitySystemComponent->SetLooseGameplayTagCount(
        AGD_NativeGameplayTags::State_OnGround_Crouching, 1);

    Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
}

void AAGD_BaseCharacter::OnEndCrouch(float HalfHeightAdjust,
                                     float ScaledHalfHeightAdjust)
{
    AbilitySystemComponent->SetLooseGameplayTagCount(
        AGD_NativeGameplayTags::State_OnGround_Crouching, 0);

    Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

    if (IsLocallyControlled()) {
        if (TriedToJump != 0.f) {
            const float UnCrouchTime =
                UGameplayStatics::GetRealTimeSeconds(GetWorld()) - TriedToJump;

            TriedToJump = 0.f;

            if (UnCrouchTime < .15f) {
                if (CanJump()) {
                    FTimerHandle UnusedHandle;
                    GetWorldTimerManager().SetTimer(
                        UnusedHandle, this, &ACharacter::Jump, 0.05f, false);
                }
            }
        }
    }
}

void AAGD_BaseCharacter::MaxMovementSpeedValueChanged(
    const FOnAttributeChangeData& Data)
{
    GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}

void AAGD_BaseCharacter::SendGameplayEvent(FGameplayTag InputTag)
{
    if (IsLocallyControlled()) {
        FGameplayEventData Payload;

        Payload.Instigator = this;
        Payload.EventTag = InputTag;

        UE_LOGFMT(LogBaseCharacter, Log, "Send Tag: {0}",
                  InputTag.GetTagName().ToString());

        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, InputTag,
                                                                 Payload);
    }
}

void AAGD_BaseCharacter::SendGameplayEvent(FGameplayTag InputTagToggleOn,
                                           FGameplayTag InputTagToggleOff)
{
    if (IsLocallyControlled()) {
        const bool bToggleState = ToggleState.Contains(InputTagToggleOn)
                                      ? ToggleState[InputTagToggleOn]
                                      : false;

        ToggleState.Add(InputTagToggleOn) = !bToggleState;

        FGameplayTag Tag = bToggleState ? InputTagToggleOff : InputTagToggleOn;

        UE_LOGFMT(LogBaseCharacter, Log, "Toggle Tag: {0} - ToggleState: {1}",
                  Tag.GetTagName().ToString(), bToggleState);

        FGameplayEventData Payload;
        Payload.Instigator = this;
        Payload.EventTag = Tag;

        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, Tag,
                                                                 Payload);
    }
}

void AAGD_BaseCharacter::ToggleCrouch(const FInputActionValue& InputActionValue)
{
    if (bIsCrouched || GetCharacterMovement()->bWantsToCrouch) {
        UnCrouch();
    }
    else if (GetCharacterMovement()->IsMovingOnGround()) {
        Crouch();
    }
}

void AAGD_BaseCharacter::StartJump(const FInputActionValue& Value)
{
    if (bIsCrouched) {
        UnCrouch();

        TriedToJump = UGameplayStatics::GetRealTimeSeconds(GetWorld());
    }
    else {
        Jump();
    }
}

void AAGD_BaseCharacter::StopJump(const FInputActionValue& Value)
{
    StopJumping();
}

void AAGD_BaseCharacter::OnJumped_Implementation()
{
    if (HasAuthority()) {
        JumpActiveHandle = AbilitySystemComponent->ApplyGEToSelf(
            CharacterDataAsset->CharacterData.JumpEffect, 0);

        UE_LOGFMT(LogBaseCharacter, Log, "Character Jumped");
    }

    Super::OnJumped_Implementation();
}

void AAGD_BaseCharacter::Landed(const FHitResult& Hit)
{
    if (HasAuthority()) {
        AbilitySystemComponent->RemoveActiveGameplayEffect(JumpActiveHandle);

        UE_LOGFMT(LogBaseCharacter, Log, "Character Landed");
    }

    Super::Landed(Hit);
}
