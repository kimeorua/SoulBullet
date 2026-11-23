// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SB_GameLevelGameMode.h"

#include "Character/SB_PlayerCharacter.h"
#include "DeveloperSettings/SB_DeveloperSettings_GameMode.h"
#include "PlayerController/SB_PlayerController.h"


ASB_GameLevelGameMode::ASB_GameLevelGameMode()
{
	DefaultPawnClass = ASB_PlayerCharacter::StaticClass();
	PlayerControllerClass = ASB_PlayerController::StaticClass();
}

void ASB_GameLevelGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	if (const USB_DeveloperSettings_GameMode* GameModeSetting = USB_DeveloperSettings_GameMode::Get())
	{
		if (!GameModeSetting->DefaultPawnClass.IsNull())
		{
			if (UClass* LoadedPawnClass = GameModeSetting->DefaultPawnClass.LoadSynchronous())
			{
				DefaultPawnClass = LoadedPawnClass;
			}
		}

		if (!GameModeSetting->PlayerControllerClass.IsNull())
		{
			if (UClass* LoadedControllerClass = GameModeSetting->PlayerControllerClass.LoadSynchronous())
			{
				PlayerControllerClass = LoadedControllerClass;
			}
		}
	}
}