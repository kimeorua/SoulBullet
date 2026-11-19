// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/SB_LevelTransitionSubsystem.h"

#include "DataAsset/SB_LevelDataAsset.h"
#include "DeveloperSettings/SB_DeveloperSetting_Level.h"
#include "Kismet/GameplayStatics.h"


void USB_LevelTransitionSubsystem::MoveToGameLevel()
{
	if (const USB_DeveloperSetting_Level* Levels = USB_DeveloperSetting_Level::Get())
	{
		if (Levels->LevelDataAsset.IsValid())
		{
			LevelDA = Cast<USB_LevelDataAsset>(Levels->LevelDataAsset.TryLoad());
		}
	}
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelDA->GameLevel);
}
