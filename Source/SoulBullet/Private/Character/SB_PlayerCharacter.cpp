// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SB_PlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Component/Input/SB_EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "SB_Tags.h"
#include "GAS/ASC/SB_AbilitySystemComponent.h"
#include "PlayerController/SB_PlayerController.h"


ASB_PlayerCharacter::ASB_PlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 200.0f;
	SpringArmComponent->SocketOffset = FVector(0.0f, 20.0f, 80.0f);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

void ASB_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (ASB_PlayerController* PC = Cast<ASB_PlayerController>(GetController()))
	{
		PC->SettingInputMode(EInputMode::InGame);
	}
}

void ASB_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ASB_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) { return; }

	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	if (!LocalPlayer) { return; }
	
	if (!InputDataAsset) { return; }
	
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
	{
		SubSystem->AddMappingContext(InputDataAsset->GetIMC(), 0);
	}
	
	USB_EnhancedInputComponent* SB_InputComp = Cast<USB_EnhancedInputComponent>(PlayerInputComponent);
	
	if (!SB_InputComp) { return; }
	
	SB_InputComp->BindNativeInputAction(InputDataAsset, SB_Tag::SB_Player_Input_Move, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
	SB_InputComp->BindNativeInputAction(InputDataAsset, SB_Tag::SB_Player_Input_Look, ETriggerEvent::Triggered, this, &ThisClass::InputLook);
}

void ASB_PlayerCharacter::InputMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

	if (MovementVector.Y != 0.0f)
	{
		const FVector ForwardDirection = MovementRotator.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.0f)
	{
		const FVector RightDirection = MovementRotator.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASB_PlayerCharacter::InputLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.0f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.0f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASB_PlayerCharacter::Input_AbilityInputTagPressed(FGameplayTag InInputTag) const
{
	SB_ASC->OnAbilityInputPressed(InInputTag);
}

void ASB_PlayerCharacter::Input_AbilityInputTagReleased(FGameplayTag InInputTag) const
{
	SB_ASC->OnAbilityInputReleased(InInputTag);
}
