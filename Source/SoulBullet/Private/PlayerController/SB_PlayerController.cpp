// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/SB_PlayerController.h"

#include "EnhancedInputSubsystems.h"


void ASB_PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsLocalController() && DefaultInputMappingContext)
	{
		if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSubsystem->RemoveMappingContext(DefaultInputMappingContext);
			}
		}
	}

	Super::EndPlay(EndPlayReason);
}

void ASB_PlayerController::SettingInputMode(EInputMode InputMode)
{
	switch (InputMode)
	{
	case EInputMode::InGame:
		{
			bShowMouseCursor = false;
			FInputModeGameOnly InputModeGameOnly;
			SetInputMode(InputModeGameOnly);
			break;
		}
		
		
	case EInputMode::UIOnly:
		{
			bShowMouseCursor = true;
			FInputModeUIOnly InputModeUIOnly;
			InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(InputModeUIOnly);
			break;
		}
	default:
		break;
	}
}

void ASB_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsLocalController()) { return; }
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (DefaultInputMappingContext)
			{
				InputSubsystem->AddMappingContext(DefaultInputMappingContext, 0);
			}
		}
	}
	SettingInputMode(EInputMode::InGame);
}
