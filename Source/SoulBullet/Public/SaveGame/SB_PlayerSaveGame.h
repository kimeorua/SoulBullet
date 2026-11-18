// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SB_PlayerSaveGame.generated.h"

UCLASS()
class SOULBULLET_API USB_PlayerSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	inline static const FString SaveSlotName = TEXT("SaveSlot");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int32 TestInt = 0;
};
