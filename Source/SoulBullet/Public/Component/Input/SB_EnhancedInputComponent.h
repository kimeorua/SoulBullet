// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/SB_InputDataAsset.h"
#include "SB_EnhancedInputComponent.generated.h"

UCLASS()
class SOULBULLET_API USB_EnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunc>
	inline void BindNativeInputAction(const USB_InputDataAsset* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	inline void BindAbilityInputAction(const USB_InputDataAsset* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

template <class UserObject, typename CallbackFunc>
void USB_EnhancedInputComponent::BindNativeInputAction(const USB_InputDataAsset* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent,
	UserObject* ContextObject, CallbackFunc Func)
{
	if (!InInputConfig) return;
	
	if (const UInputAction* IA = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(IA, TriggerEvent, ContextObject, Func);
	}
}

template <class UserObject, typename CallbackFunc>
void USB_EnhancedInputComponent::BindAbilityInputAction(const USB_InputDataAsset* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc,
	CallbackFunc InputReleasedFunc)
{
	if (!InInputConfig || !ContextObject) {return;}
	for (const FSB_InputConfig& ActionConfig : InInputConfig->GetAbilityInputConfigs())
	{
		if (!ActionConfig.IsValid()) { continue; }
		
		BindAction(ActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, ActionConfig.InputTag);
		BindAction(ActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, ActionConfig.InputTag);
	}
};