// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/SB_MainLevelPlayerController.h"

#include "EnhancedInputSubsystems.h"


void ASB_MainLevelPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsLocalController()) { return; }

	bShowMouseCursor = true;

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (MenuInputMappingContext)
			{
				InputSubsystem->AddMappingContext(MenuInputMappingContext, 0);
			}
		}
	}
	
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
}

void ASB_MainLevelPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsLocalController() && MenuInputMappingContext)
	{
		if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSubsystem->RemoveMappingContext(MenuInputMappingContext);
			}
		}
	}

	Super::EndPlay(EndPlayReason);
}
