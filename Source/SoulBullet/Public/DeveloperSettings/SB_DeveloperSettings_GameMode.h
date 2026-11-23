// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SB_DeveloperSettings_GameMode.generated.h"

class ASB_PlayerController;
class ASB_PlayerCharacter;
/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, DisplayName = "Soul Bullet GameMode Settings")
class SOULBULLET_API USB_DeveloperSettings_GameMode : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Level DataAsset")
	TSoftClassPtr<ASB_PlayerCharacter>DefaultPawnClass;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Level DataAsset")
	TSoftClassPtr<ASB_PlayerController> PlayerControllerClass;
	
	static const USB_DeveloperSettings_GameMode* Get() { return GetDefault<USB_DeveloperSettings_GameMode>();}
};
