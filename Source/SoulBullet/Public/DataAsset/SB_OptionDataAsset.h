// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/SB_BaseDataAsset.h"
#include "SB_OptionDataAsset.generated.h"

class USoundMix;
class USoundClass;

UCLASS()
class SOULBULLET_API USB_OptionDataAsset : public USB_BaseDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundMix> DefaultSoundMix;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundClass> MasterSoundClass;
	
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif

	virtual bool IsRuntimeDataValid() const override;
};
