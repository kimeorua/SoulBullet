// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/SB_BaseDataAsset.h"
#include "SB_LevelDataAsset.generated.h"

class UWorld;

UCLASS()
class SOULBULLET_API USB_LevelDataAsset : public USB_BaseDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level")
	TSoftObjectPtr<UWorld> GameLevel;
	
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif

	virtual bool IsRuntimeDataValid() const override;
};
