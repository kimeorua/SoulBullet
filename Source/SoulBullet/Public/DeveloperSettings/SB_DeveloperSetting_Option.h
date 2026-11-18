// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SB_DeveloperSetting_Option.generated.h"

UCLASS(Config = Game, DefaultConfig, DisplayName = "Soul Bullet Settings")
class SOULBULLET_API USB_DeveloperSetting_Option : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Option DataAsset")
	FSoftObjectPath OptionDataAsset;

	static const USB_DeveloperSetting_Option* Get() { return GetDefault<USB_DeveloperSetting_Option>();}
};
