// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/SB_InputDataAsset.h"

#include "Log/SB_Log.h"
#include "Misc/DataValidation.h"

USB_InputDataAsset::USB_InputDataAsset()
{
}

#if WITH_EDITOR
EDataValidationResult USB_InputDataAsset::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (NativeInputConfigs.IsEmpty() && AbilityInputConfigs.IsEmpty())
	{
		Context.AddError(FText::FromString(FString::Printf(TEXT("[%s] NativeInputConfigs와 AbilityInputConfigs가 모두 비어있습니다."), *GetName())));
		return EDataValidationResult::Invalid;
	}

	TSet<FGameplayTag> UsedTags;
	auto ValidateConfigs = [&](const TArray<FSB_InputConfig>& Configs, const TCHAR* ArrayName)
	{
		for (const FSB_InputConfig& Config : Configs)
		{
			if (!Config.IsValid())
			{
				Context.AddError(FText::FromString(FString::Printf(TEXT("[%s] %s에 지정되지 않은 InputTag 또는 InputAction이 있습니다."), *GetName(), ArrayName)));
				Result = EDataValidationResult::Invalid;
				continue;
			}

			if (UsedTags.Contains(Config.InputTag))
			{
				Context.AddError(FText::FromString(FString::Printf(TEXT("[%s] %s에 중복된 InputTag(%s)가 등록되어 있습니다."), *GetName(), ArrayName, *Config.InputTag.ToString())));
				Result = EDataValidationResult::Invalid;
			}
			else
			{
				UsedTags.Add(Config.InputTag);
			}
		}
	};

	ValidateConfigs(NativeInputConfigs, TEXT("NativeInputConfigs"));
	ValidateConfigs(AbilityInputConfigs, TEXT("AbilityInputConfigs"));

	return Result;
}
#endif

bool USB_InputDataAsset::IsRuntimeDataValid() const
{
	bool bIsBaseValid = Super::IsRuntimeDataValid();

	if (NativeInputConfigs.IsEmpty() && AbilityInputConfigs.IsEmpty())
	{
		SB_Log(LogSBData, Error, TEXT("[%s] 런타임 데이터 검증 실패: 입력 설정 배열이 모두 비어있습니다."), *GetName());
		return false;
	}

	auto CheckConfigsValid = [&](const TArray<FSB_InputConfig>& Configs, const TCHAR* ArrayName) -> bool
	{
		for (const FSB_InputConfig& Config : Configs)
		{
			if (!Config.IsValid())
			{
				SB_Log(LogSBData, Error, TEXT("[%s] 런타임 데이터 검증 실패: %s에 유효하지 않은 항목이 있습니다."), *GetName(), ArrayName);
				return false;
			}
		}
		return true;
	};

	const bool bNativeValid = CheckConfigsValid(NativeInputConfigs, TEXT("NativeInputConfigs"));
	const bool bAbilityValid = CheckConfigsValid(AbilityInputConfigs, TEXT("AbilityInputConfigs"));

	return bIsBaseValid && bNativeValid && bAbilityValid;
}

const UInputAction* USB_InputDataAsset::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	if (!InInputTag.IsValid()) { return nullptr; }

	for (const FSB_InputConfig& Config : NativeInputConfigs)
	{
		if (Config.InputTag == InInputTag && Config.InputAction)
		{
			return Config.InputAction;
		}
	}

	SB_Log(LogSBData, Warning, TEXT("[%s] 태그(%s)에 해당하는 NativeInputAction을 찾을 수 없습니다."), *GetName(), *InInputTag.ToString());
	return nullptr;
}