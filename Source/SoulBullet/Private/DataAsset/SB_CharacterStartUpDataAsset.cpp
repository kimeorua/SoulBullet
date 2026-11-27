// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/SB_CharacterStartUpDataAsset.h"

#include "Misc/DataValidation.h"

#include "DataAsset/SB_InputDataAsset.h"
#include "GAS/Abiliy/SB_BaseAbility.h"
#include "GAS/ASC/SB_AbilitySystemComponent.h"
#include "Log/SB_Log.h"


USB_CharacterStartUpDataAsset::USB_CharacterStartUpDataAsset()
{
}

void USB_CharacterStartUpDataAsset::ApplyStartUpDataToASC(USB_AbilitySystemComponent* InASCToGive, int32 ApplyLevel) const
{
	if (!InASCToGive) { return; }

	GiveAbilitiesToASC(InASCToGive, ApplyLevel);
	ApplyStartUpEffectsToASC(InASCToGive, ApplyLevel);
}

void USB_CharacterStartUpDataAsset::GiveAbilitiesToASC(USB_AbilitySystemComponent* InASCToGive, int32 ApplyLevel) const
{
	for (const TSubclassOf<USB_BaseAbility>& AbilityClass : AbilityByEvent)
	{
		if (!IsValid(AbilityClass)) { continue; }

		FGameplayAbilitySpec AbilitySpec(AbilityClass);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}

void USB_CharacterStartUpDataAsset::ApplyStartUpEffectsToASC(USB_AbilitySystemComponent* InASCToGive, int32 ApplyLevel) const
{
	for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
	{
		if (!IsValid(EffectClass)) { continue; }

		const UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
		FGameplayEffectContextHandle ContextHandle = InASCToGive->MakeEffectContext();
		ContextHandle.AddSourceObject(InASCToGive->GetAvatarActor());

		InASCToGive->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, ContextHandle);
	}
}

template <typename ErrorFunc>
bool USB_CharacterStartUpDataAsset::ValidateBaseStartUpData(ErrorFunc&& OnError) const
{
	bool bAllValid = true;

	for (const TSubclassOf<USB_BaseAbility>& EventAbility : AbilityByEvent)
	{
		if (!IsValid(EventAbility))
		{
			OnError(TEXT("AbilityByEvent에 유효하지 않은 Ability 클래스가 있습니다."));
			bAllValid = false;
		}
	}

	for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
	{
		if (!IsValid(EffectClass))
		{
			OnError(TEXT("StartUpGameplayEffects에 유효하지 않은 GameplayEffect 클래스가 있습니다."));
			bAllValid = false;
		}
	}

	return bAllValid;
}
	
#if WITH_EDITOR
EDataValidationResult USB_CharacterStartUpDataAsset::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	const bool bBaseValid = ValidateBaseStartUpData([&](const TCHAR* Message)
	{
		Context.AddError(FText::FromString(FString::Printf(TEXT("[%s] %s"), *GetName(), Message)));
	});

	if (!bBaseValid)
	{
		Result = EDataValidationResult::Invalid;
	}

	return Result;
}
#endif

bool USB_CharacterStartUpDataAsset::IsRuntimeDataValid() const
{
	const bool bIsBaseValid = Super::IsRuntimeDataValid();

	const bool bStartUpValid = ValidateBaseStartUpData([&](const TCHAR* Message)
	{
		SB_Log(LogSBData, Error, TEXT("[%s] 런타임 데이터 검증 실패: %s"), *GetName(), Message);
	});

	return bIsBaseValid && bStartUpValid;
}