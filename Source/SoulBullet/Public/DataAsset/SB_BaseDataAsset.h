// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SB_BaseDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SOULBULLET_API USB_BaseDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	USB_BaseDataAsset();
	
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
	
	UFUNCTION(BlueprintPure)
	virtual bool IsRuntimeDataValid() const;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataAsset | MetaData")
	FText DisplayName;
};
