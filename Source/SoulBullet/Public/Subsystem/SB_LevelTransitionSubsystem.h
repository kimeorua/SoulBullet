// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SB_LevelTransitionSubsystem.generated.h"

class USB_LevelDataAsset;

UCLASS()
class SOULBULLET_API USB_LevelTransitionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void MoveToGameLevel();
	
private:
	UPROPERTY()
	TObjectPtr<USB_LevelDataAsset> LevelDA;
};
