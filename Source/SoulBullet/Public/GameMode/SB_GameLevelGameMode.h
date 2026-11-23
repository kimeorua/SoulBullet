// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SB_GameLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SOULBULLET_API ASB_GameLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASB_GameLevelGameMode();
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};
