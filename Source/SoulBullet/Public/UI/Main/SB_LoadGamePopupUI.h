// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Main/SB_BasePopupUI.h"
#include "SB_LoadGamePopupUI.generated.h"

class USB_BaseSaveSlot;

UCLASS()
class SOULBULLET_API USB_LoadGamePopupUI : public USB_BasePopupUI
{
	GENERATED_BODY()
public:
	USB_LoadGamePopupUI();
	
	virtual void InitFocus() override;
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USB_BaseSaveSlot> SaveSlots;
	
	void OnClickAction(int Index);
};
