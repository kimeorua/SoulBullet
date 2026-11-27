// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/SB_BaseDataAsset.h"
#include "SB_CharacterStartUpDataAsset.generated.h"

class USB_BaseAbility;
class USB_AbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class SOULBULLET_API USB_CharacterStartUpDataAsset : public USB_BaseDataAsset
{
	GENERATED_BODY()
	
public:
	USB_CharacterStartUpDataAsset();
	
	void ApplyStartUpDataToASC(USB_AbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) const;
	
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
	
	virtual bool IsRuntimeDataValid() const override;
	
protected:
	virtual void GiveAbilitiesToASC(USB_AbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) const;
	void ApplyStartUpEffectsToASC(USB_AbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StartUpData|Ability")
	TArray<TSubclassOf<USB_BaseAbility>> AbilityByEvent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StartUpData|Effect")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;
	
private:
	template<typename ErrorFunc>
	bool ValidateBaseStartUpData(ErrorFunc&& OnError) const;
};