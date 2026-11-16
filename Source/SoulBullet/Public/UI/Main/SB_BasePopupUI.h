// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "SB_BasePopupUI.generated.h"

class UCommonButtonBase;
class UWidget;
class UBackgroundBlur;

UCLASS()
class SOULBULLET_API USB_BasePopupUI : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	USB_BasePopupUI();
	
	virtual void InitFocus();
	
protected:
	virtual void NativeConstruct() override;
	
	virtual bool NativeOnHandleBackAction() override;
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UBackgroundBlur> Blur;
};