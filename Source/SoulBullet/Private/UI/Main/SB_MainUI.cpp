// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Main/SB_MainUI.h"

#include "CommonButtonBase.h"
#include "Log/SB_Log.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "UI/Main/SB_BasePopupUI.h"

USB_MainUI::USB_MainUI()
{
}

void USB_MainUI::OnClickGameStart()
{
	if (IsValid(GameStartPopupUI))
	{
		USB_BasePopupUI* CreatedPopup = MenuStack->AddWidget<USB_BasePopupUI>(GameStartPopupUI);
		
		if (IsValid(CreatedPopup))
		{
			CreatedPopup->InitFocus();
		}
	}
}

void USB_MainUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (GameStartButton)
	{
		GameStartButton->SetFocus();
		
		GameStartButton->OnClicked().AddUObject(this, &USB_MainUI::OnClickGameStart);
	}
}

UWidget* USB_MainUI::NativeGetDesiredFocusTarget() const
{
	return GameStartButton ? GameStartButton : Super::NativeGetDesiredFocusTarget();
}