// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AGD_BaseCharacter.h"

#include "ActiveGameplayEffectHandle.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayEffectTypes.h"
#include "InputActionValue.h"
#include "Manager/AGD_TagManager.h"
#include "Misc/AssertionMacros.h"
#include "Player/AGD_BasePlayerState.h"
#include "Templates/Casts.h"
#include "GAS/AGD_AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

DEFINE_LOG_CATEGORY(LogBaseCharacter);

// Sets default values
AAGD_BaseCharacter::AAGD_BaseCharacter()
{
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
}

void AAGD_BaseCharacter::BeginPlay()
{
    // Call the base class
    Super::BeginPlay();
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
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }

    // Set up action bindings
    if (UEnhancedInputComponent* EnhancedInputComponent =
            Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

        // Jumping
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started,
                                           this,
                                           &AAGD_BaseCharacter::OnJumpStarted);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed,
                                           this,
                                           &AAGD_BaseCharacter::OnJumpEnded);

        // Moving
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,
                                           this, &AAGD_BaseCharacter::Move);

        // Looking
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered,
                                           this, &AAGD_BaseCharacter::Look);

        // Crouching
        EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started,
                                           this, &AAGD_BaseCharacter::OnCrouch);
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

void AAGD_BaseCharacter::OnJumpStarted(const FInputActionValue& Value)
{
    FGameplayEventData Payload;

    Payload.Instigator = this;
    Payload.EventTag = JumpEventTag;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, JumpEventTag,
                                                             Payload);
}

void AAGD_BaseCharacter::OnJumpEnded(const FInputActionValue& Value)
{
    StopJumping();
}

void AAGD_BaseCharacter::OnCrouch(const FInputActionValue& Value)
{
    FGameplayEventData Payload;

    Payload.Instigator = this;
    Payload.EventTag = CrouchEventTag;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        this, CrouchEventTag, Payload);
}

void AAGD_BaseCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
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
    FGameplayEventData Payload;

    Payload.Instigator = this;
    Payload.EventTag = FAGD_TagManager::Get().Event_Ability_OnGround_Crouch;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        this, FAGD_TagManager::Get().Event_Ability_OnGround_Crouch, Payload);

    Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
}

void AAGD_BaseCharacter::OnEndCrouch(float HalfHeightAdjust,
                                     float ScaledHalfHeightAdjust)
{
    FGameplayEventData Payload;

    Payload.Instigator = this;
    Payload.EventTag = FAGD_TagManager::Get().Event_Ability_OnGround_UnCrouch;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        this, FAGD_TagManager::Get().Event_Ability_OnGround_UnCrouch, Payload);

    Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
}

void AAGD_BaseCharacter::OnJumped_Implementation()
{
    FGameplayEventData Payload;

    Payload.Instigator = this;
    Payload.EventTag = FAGD_TagManager::Get().Event_Ability_InAir_Jumped;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        this, FAGD_TagManager::Get().Event_Ability_InAir_Jumped, Payload);

    Super::OnJumped_Implementation();
}