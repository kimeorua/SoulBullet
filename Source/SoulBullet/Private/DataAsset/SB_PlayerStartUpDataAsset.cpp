// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/SB_PlayerStartUpDataAsset.h"

#include "Misc/DataValidation.h"

#include "GAS/ASC/SB_AbilitySystemComponent.h"
#include "Log/SB_Log.h"


void USB_PlayerStartUpDataAsset::GiveAbilitiesToASC(USB_AbilitySystemComponent* InASCToGive, int32 ApplyLevel) const
{
	Super::GiveAbilitiesToASC(InASCToGive, ApplyLevel);
	
	if (!InASCToGive) { return; }
	
	for (const FSB_AbilityConfig& AbilityConfig : AbilityByInput)
	{
		if (!AbilityConfig.IsValid()) { continue; }

		FGameplayAbilitySpec AbilitySpec(AbilityConfig.Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityConfig.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}

template <typename ErrorFunc>
bool USB_PlayerStartUpDataAsset::ValidatePlayerStartUpData(ErrorFunc&& OnError) const
{
	if (AbilityByInput.IsEmpty())
	{
		OnError(TEXT("AbilityByInput이 비어있습니다."));
		return false;
	}

	bool bAllValid = true;
	TSet<FGameplayTag> UsedInputTags;

	for (const FSB_AbilityConfig& AbilityConfig : AbilityByInput)
	{
		if (!AbilityConfig.IsValid())
		{
			OnError(TEXT("AbilityByInput에 유효하지 않은 Ability 또는 InputTag가 있습니다."));
			bAllValid = false;
			continue;
		}

		if (UsedInputTags.Contains(AbilityConfig.InputTag))
		{
			OnError(TEXT("AbilityByInput에 중복된 InputTag가 등록되어 있습니다."));
			bAllValid = false;
		}
		else
		{
			UsedInputTags.Add(AbilityConfig.InputTag);
		}
	}

	return bAllValid;
}

EDataValidationResult USB_PlayerStartUpDataAsset::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	const bool bPlayerValid = ValidatePlayerStartUpData([&](const TCHAR* Message)
	{
		Context.AddError(FText::FromString(FString::Printf(TEXT("[%s] %s"), *GetName(), Message)));
	});

	if (!bPlayerValid)
	{
		Result = EDataValidationResult::Invalid;
	}

	return Result;
}

bool USB_PlayerStartUpDataAsset::IsRuntimeDataValid() const
{
	const bool bIsSuperValid = Super::IsRuntimeDataValid();

	const bool bPlayerValid = ValidatePlayerStartUpData([&](const TCHAR* Message)
	{
		SB_Log(LogSBData, Error, TEXT("[%s] 런타임 데이터 검증 실패: %s"), *GetName(), Message);
	});

	return bIsSuperValid && bPlayerValid;
}
