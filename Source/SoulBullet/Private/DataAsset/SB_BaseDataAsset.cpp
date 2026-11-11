#include "DataAsset/SB_BaseDataAsset.h"

#include "Log/SB_Log.h"
#include "Misc/DataValidation.h"


USB_BaseDataAsset::USB_BaseDataAsset()
{
}

#if WITH_EDITOR
EDataValidationResult USB_BaseDataAsset::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);
	
	if (DisplayName.IsEmpty())
	{
		Context.AddError(FText::FromString(FString::Printf(TEXT("[%s] DisplayName이 지정되지 않았습니다!"), *GetName())));
		Result = EDataValidationResult::Invalid;
	}
	return Result;
}
#endif

bool USB_BaseDataAsset::IsRuntimeDataValid() const
{
	bool bIsValid = !DisplayName.IsEmpty();
	
	if (!bIsValid)
	{
		SB_Log(LogSBData, Error, TEXT("[%s] 런타임 데이터 검증 실패: DisplayName이 비어있습니다."), *GetName());
	}
	
	return bIsValid;
}
