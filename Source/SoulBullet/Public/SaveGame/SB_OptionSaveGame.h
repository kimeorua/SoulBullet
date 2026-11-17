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
	inline static const FString SaveSlotName = TEXT("OptionSloat");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Sound")
	float SavedVolume = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Graphic")
	int32 SavedGraphicQualityLevel = 3;
};
