// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/SB_OptionGameInstanceSubsystem.h"

#include "Kismet/GameplayStatics.h"

#include "SaveGame/SB_OptionSaveGame.h"
#include "DeveloperSettings/SB_DeveloperSetting_Option.h"
#include "DataAsset/SB_OptionDataAsset.h"
#include "GameFramework/GameUserSettings.h"


void USB_OptionGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (const USB_DeveloperSetting_Option* Settings = USB_DeveloperSetting_Option::Get())
	{
		if (Settings->OptionDataAsset.IsValid())
		{
			OptionDA = Cast<USB_OptionDataAsset>(Settings->OptionDataAsset.TryLoad());
		}
	}
	
	if (USB_OptionSaveGame* LoadedGame = Cast<USB_OptionSaveGame>(UGameplayStatics::LoadGameFromSlot(USB_OptionSaveGame::SaveSlotName, 0)))
	{
		CurrentVolume = LoadedGame->SavedVolume;
		
		if (UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings())
		{
			UserSettings->SetOverallScalabilityLevel(LoadedGame->SavedGraphicQualityLevel);
			UserSettings->ApplySettings(false);
		}
	}
	else
	{
		CurrentVolume = 1.0f;
	}
}

void USB_OptionGameInstanceSubsystem::SetMasterVolume(float NewVolume)
{
	CurrentVolume = FMath::Clamp(NewVolume, 0.0f, 1.0f);
	
	if (OptionDA)
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), OptionDA->DefaultSoundMix, OptionDA->MasterSoundClass, CurrentVolume, 1.0f, true);
	}
	
	if (USB_OptionSaveGame* SaveGameInstance = Cast<USB_OptionSaveGame>(UGameplayStatics::CreateSaveGameObject(USB_OptionSaveGame::StaticClass())))
	{
		SaveGameInstance->SavedVolume = CurrentVolume;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, USB_OptionSaveGame::SaveSlotName, 0);
	}
}

void USB_OptionGameInstanceSubsystem::ApplyInitialVolume()
{
	if (OptionDA && GetWorld())
	{
		if (OptionDA->DefaultSoundMix)
		{
			UGameplayStatics::PushSoundMixModifier(GetWorld(), OptionDA->DefaultSoundMix);
		}
		
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), OptionDA->DefaultSoundMix, OptionDA->MasterSoundClass, CurrentVolume, 1.0f, true);
	}
}

void USB_OptionGameInstanceSubsystem::SetGraphicQuality(int32 NewQualityLevel)
{
	if (UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings())
	{
		int32 ClampedLevel = FMath::Clamp(NewQualityLevel, 0, 4);
		
		UserSettings->SetOverallScalabilityLevel(ClampedLevel);
		UserSettings->ApplySettings(false);
		
		if (USB_OptionSaveGame* SaveGameInstance = Cast<USB_OptionSaveGame>(UGameplayStatics::CreateSaveGameObject(USB_OptionSaveGame::StaticClass())))
		{
			SaveGameInstance->SavedGraphicQualityLevel = ClampedLevel;
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, USB_OptionSaveGame::SaveSlotName, 0);
		}
	}
}

int32 USB_OptionGameInstanceSubsystem::GetGraphicQuality() const
{
	if (const UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings())
	{
		return UserSettings->GetOverallScalabilityLevel();
	}
	return 3;
}