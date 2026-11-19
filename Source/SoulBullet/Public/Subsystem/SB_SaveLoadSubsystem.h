// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SB_SaveLoadSubsystem.generated.h"

class USB_LevelDataAsset;
class USB_PlayerSaveGame;

UCLASS()
class SOULBULLET_API USB_SaveLoadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void SaveGameToSlot_Menu(int32 SlotIndex);
	bool LoadGameFromSlot_Menu(int32 SlotIndex);
	bool DoesSlotExist(int32 SlotIndex) const;
	USB_PlayerSaveGame* GetCurrentSaveGameData() const;
	void MoveToGameLevel();

private:
	UPROPERTY()
	TObjectPtr<USB_PlayerSaveGame> CurrentSaveGameData;
	
	UPROPERTY()
	TObjectPtr<USB_LevelDataAsset> LevelDA;
};
