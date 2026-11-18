// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SB_SaveLoadSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SOULBULLET_API USB_SaveLoadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void SaveGameToSlot_Menu(int32 SlotIndex);
	bool LoadGameFromSlot_Menu(int32 SlotIndex);
	bool DoesSlotExist(int32 SlotIndex) const;

private:
	UPROPERTY()
	TObjectPtr<class USB_PlayerSaveGame> CurrentSaveGameData;
};
