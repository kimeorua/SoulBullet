// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/SB_LoadGamePopupUI.h"

#include "CommonButtonBase.h"
#include "Subsystem/SB_SaveLoadSubsystem.h"
#include "UI/Main/SB_BaseSaveSlot.h"


USB_LoadGamePopupUI::USB_LoadGamePopupUI()
{
}

void USB_LoadGamePopupUI::InitFocus()
{
	if (SaveSlots && SaveSlots->GetFirstSlotButton())
	{
		SaveSlots->GetFirstSlotButton()->SetFocus();
	}
}

void USB_LoadGamePopupUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void USB_LoadGamePopupUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	SaveSlots->OnClickAction.AddUObject(this, &USB_LoadGamePopupUI::OnClickAction);
}

UWidget* USB_LoadGamePopupUI::NativeGetDesiredFocusTarget() const
{
	return Super::NativeGetDesiredFocusTarget();
}

void USB_LoadGamePopupUI::OnClickAction(int Index)
{
	if (UGameInstance* GI = GetGameInstance())
	{
		if (USB_SaveLoadSubsystem* SaveSubsystem = GI->GetSubsystem<USB_SaveLoadSubsystem>())
		{
			if (SaveSubsystem->LoadGameFromSlot_Menu(Index))
			{
				SaveSubsystem->MoveToGameLevel();
			}
		}
	}
}