// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/SB_GameStartPopup.h"
#include "CommonButtonBase.h"

USB_GameStartPopup::USB_GameStartPopup()
{
}

void USB_GameStartPopup::InitFocus()
{
	if (NewGameButton)
	{
		NewGameButton->SetFocus();
	}
}

void USB_GameStartPopup::OnBackButton()
{
	DeactivateWidget();
}

void USB_GameStartPopup::NativeConstruct()
{
	Super::NativeConstruct();
	
	BackButton->OnClicked().AddUObject(this, &USB_GameStartPopup::OnBackButton);
}

UWidget* USB_GameStartPopup::NativeGetDesiredFocusTarget() const
{
	return NewGameButton ? NewGameButton : Super::NativeGetDesiredFocusTarget();
}