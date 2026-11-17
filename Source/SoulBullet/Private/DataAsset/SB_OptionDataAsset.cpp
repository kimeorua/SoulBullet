// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/SB_OptionDataAsset.h"

#include "Log/SB_Log.h"
#include "Misc/DataValidation.h"


EDataValidationResult USB_OptionDataAsset::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (!DefaultSoundMix)
	{
		Context.AddError(FText::FromString(TEXT("DefaultSoundMix가 할당되지 않았습니다!")));
		Result = EDataValidationResult::Invalid;
	}

	if (!MasterSoundClass)
	{
		Context.AddError(FText::FromString(TEXT("MasterSoundClass가 할당되지 않았습니다!")));
		Result = EDataValidationResult::Invalid;
	}

	return Result;
}

bool USB_OptionDataAsset::IsRuntimeDataValid() const
{
	bool bIsDisplayNameSetting = Super::IsRuntimeDataValid();
	bool bIsSoundMixValid = DefaultSoundMix != nullptr;
	bool bIsMasterSoundValid = MasterSoundClass != nullptr;
	
	
	if (!bIsSoundMixValid)
	{
		SB_Log(LogSBData, Error, TEXT("런타임 데이터 검증 실패: DefaultSoundMix가 비어있습니다."));
	}
	
	if (bIsMasterSoundValid)
	{
		SB_Log(LogSBData, Error, TEXT("런타임 데이터 검증 실패: MasterSoundClass가 비어있습니다."));
	}
	
	return bIsDisplayNameSetting && bIsSoundMixValid && bIsMasterSoundValid;
}