// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/SB_LevelDataAsset.h"

#include "Log/SB_Log.h"
#include "Misc/DataValidation.h"

EDataValidationResult USB_LevelDataAsset::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (!GameLevel)
	{
		Context.AddError(FText::FromString(TEXT("GameLevel이 할당되지 않았습니다!")));
		Result = EDataValidationResult::Invalid;
	}
	return Result;
}

bool USB_LevelDataAsset::IsRuntimeDataValid() const
{
	bool bIsDisplayNameSetting = Super::IsRuntimeDataValid();
	bool LevelSetting = GameLevel != nullptr;
	
	if (!LevelSetting)
	{
		SB_Log(LogSBData, Error, TEXT("런타임 데이터 검증 실패: GameLevel이 비어있습니다."));
	}
	
	return bIsDisplayNameSetting && LevelSetting;
}