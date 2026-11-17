// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Main/SB_BasePopupUI.h"
#include "SB_GameStartPopup.generated.h"

class UCommonButtonBase;

UCLASS()
class SOULBULLET_API USB_GameStartPopup : public USB_BasePopupUI
{
	GENERATED_BODY()
	
public:
	USB_GameStartPopup();
	
	virtual void InitFocus() override;
	
protected:
	virtual void NativeConstruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> NewGameButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> LoadGameButton;
};