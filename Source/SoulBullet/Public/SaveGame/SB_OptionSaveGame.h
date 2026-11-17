// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SB_OptionSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SOULBULLET_API USB_OptionSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float SavedVolume = 1.0f;
	
	inline static const FString SaveSlotName = TEXT("OptionSloat");
};
