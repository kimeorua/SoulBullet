// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SB_OptionGameInstanceSubsystem.generated.h"

class USB_OptionDataAsset;

UCLASS()
class SOULBULLET_API USB_OptionGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void SetMasterVolume(float NewVolume);
	FORCEINLINE float GetMasterVolume() const { return CurrentVolume; }
	
	UFUNCTION(BlueprintCallable)
	void ApplyInitialVolume();
	
	void SetGraphicQuality(int32 NewQualityLevel);
	int32 GetGraphicQuality() const;

private:
	float CurrentVolume = 1.0f;

	UPROPERTY()
	TObjectPtr<USB_OptionDataAsset> OptionDA;
};
