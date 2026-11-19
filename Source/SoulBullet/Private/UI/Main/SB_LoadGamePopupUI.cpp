// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/SB_LoadGamePopupUI.h"

#include "CommonButtonBase.h"
#include "Subsystem/SB_LevelTransitionSubsystem.h"
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
	
	if (UGameInstance* GI = GetGameInstance())
	{
		SaveSubsystem = GI->GetSubsystem<USB_SaveLoadSubsystem>();
		LevelTransitionSubsystem = GI->GetSubsystem<USB_LevelTransitionSubsystem>();
	}
}

void USB_LoadGamePopupUI::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	if (SaveSlots)
	{
		SaveSlots->ActivateWidget();
	}
}

UWidget* USB_LoadGamePopupUI::NativeGetDesiredFocusTarget() const
{
	if (SaveSlots)
	{
		return SaveSlots->GetFirstSlotButton();
	}
    
	return Super::NativeGetDesiredFocusTarget();
}

void USB_LoadGamePopupUI::OnClickAction(int Index)
{
	if (!SaveSubsystem || !LevelTransitionSubsystem) { return; }
	
	if (SaveSubsystem->LoadGameFromSlot(Index))
	{
		LevelTransitionSubsystem->MoveToGameLevel();
	}
}