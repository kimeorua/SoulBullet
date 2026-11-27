// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/SB_CharacterStartUpDataAsset.h"
#include "GameplayTagContainer.h"
#include "GAS/Abiliy/SB_BaseAbility.h"
#include "SB_PlayerStartUpDataAsset.generated.h"

USTRUCT(BlueprintType)
struct  FSB_AbilityConfig
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS", meta = (Categories = "SB"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<USB_BaseAbility> Ability;
	
	bool IsValid() const
	{
		return InputTag.IsValid() && (Ability != nullptr);
	}
};

UCLASS()
class SOULBULLET_API USB_PlayerStartUpDataAsset : public USB_CharacterStartUpDataAsset
{
	GENERATED_BODY()
	
public:
	virtual bool IsRuntimeDataValid() const override;

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif

protected:
	virtual void GiveAbilitiesToASC(USB_AbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) const override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StartUpData|Ability")
	TArray<FSB_AbilityConfig> AbilityByInput;

private:
	template<typename ErrorFunc>
	bool ValidatePlayerStartUpData(ErrorFunc&& OnError) const;
};