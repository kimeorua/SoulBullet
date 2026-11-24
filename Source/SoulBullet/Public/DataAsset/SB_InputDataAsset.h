// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAsset/SB_BaseDataAsset.h"
#include "SB_InputDataAsset.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct  FSB_InputConfig
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS", meta = (Categories = "SB"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UInputAction> InputAction;
	
	bool IsValid() const
	{
		return InputTag.IsValid() && (InputAction != nullptr);
	}
};

UCLASS()
class SOULBULLET_API USB_InputDataAsset : public USB_BaseDataAsset
{
	GENERATED_BODY()
public:
	USB_InputDataAsset();
	
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
	
	virtual bool IsRuntimeDataValid() const override;
	
	const UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
	const TArray<FSB_InputConfig>& GetAbilityInputConfigs() const { return AbilityInputConfigs; }
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataAsset | Input")
	TArray<FSB_InputConfig> NativeInputConfigs;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataAsset | Input")
	TArray<FSB_InputConfig> AbilityInputConfigs;
};
