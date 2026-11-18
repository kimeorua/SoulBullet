// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/SB_SaveLoadSubsystem.h"

#include "DataAsset/SB_LevelDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Log/SB_Log.h"

#include "SaveGame/SB_PlayerSaveGame.h"
#include "DeveloperSettings/SB_DeveloperSetting_Level.h"


void USB_SaveLoadSubsystem::SaveGameToSlot_Menu(int32 SlotIndex)
{
	FString TargetSlotName = FString::Printf(TEXT("%s_%d"), *USB_PlayerSaveGame::SaveSlotName, SlotIndex);
	
	if (USB_PlayerSaveGame* SaveGameInstance = Cast<USB_PlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(USB_PlayerSaveGame::StaticClass())))
	{
		SaveGameInstance->TestInt = 10;
		
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TargetSlotName, 0);
		CurrentSaveGameData = SaveGameInstance;
		
		SB_Log(LogSBCore, Warning, TEXT("[SaveSystem] %d번 슬롯 세이브 성공"), SlotIndex);
		
		MoveToGameLevel();
	}
}

bool USB_SaveLoadSubsystem::LoadGameFromSlot_Menu(int32 SlotIndex)
{
	FString TargetSlotName = FString::Printf(TEXT("%s_%d"), *USB_PlayerSaveGame::SaveSlotName, SlotIndex);

	if (UGameplayStatics::DoesSaveGameExist(TargetSlotName, 0))
	{
		CurrentSaveGameData = Cast<USB_PlayerSaveGame>(
			UGameplayStatics::LoadGameFromSlot(TargetSlotName, 0)
		);

		if (CurrentSaveGameData)
		{
			SB_Log(LogSBCore, Warning, TEXT("[SaveSystem] %d번 슬롯 로드 성공"), SlotIndex);
			return true;
		}
	}

	SB_Log(LogSBCore, Warning, TEXT("[SaveSystem] %d번 슬롯 로드 실패 (파일 없음)"), SlotIndex);
	return false;
}

bool USB_SaveLoadSubsystem::DoesSlotExist(int32 SlotIndex) const
{
	FString TargetSlotName = FString::Printf(TEXT("%s_%d"), *USB_PlayerSaveGame::SaveSlotName, SlotIndex);
	return UGameplayStatics::DoesSaveGameExist(TargetSlotName, 0);
}

void USB_SaveLoadSubsystem::MoveToGameLevel()
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
