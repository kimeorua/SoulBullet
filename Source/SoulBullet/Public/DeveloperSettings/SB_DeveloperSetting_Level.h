// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SB_DeveloperSetting_Level.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, DisplayName = "Soul Bullet Level Settings")
class SOULBULLET_API USB_DeveloperSetting_Level : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Level DataAsset")
	FSoftObjectPath LevelDataAsset;
	
	static const USB_DeveloperSetting_Level* Get() { return GetDefault<USB_DeveloperSetting_Level>();}
};
