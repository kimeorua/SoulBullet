// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Main/SB_BasePopupUI.h"

#include "CommonButtonBase.h"

USB_BasePopupUI::USB_BasePopupUI()
{
}

void USB_BasePopupUI::InitFocus()
{
}

void USB_BasePopupUI::OnBackButton()
{
	DeactivateWidget();
}

void USB_BasePopupUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	BackButton->OnClicked().AddUObject(this, &USB_BasePopupUI::OnBackButton);
}

bool USB_BasePopupUI::NativeOnHandleBackAction()
{
	DeactivateWidget();
	
	return true;
}