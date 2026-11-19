// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/SB_NewGamePopup.h"

#include "CommonButtonBase.h"
#include "Subsystem/SB_LevelTransitionSubsystem.h"
#include "Subsystem/SB_SaveLoadSubsystem.h"
#include "UI/Main/SB_BaseSaveSlot.h"


USB_NewGamePopup::USB_NewGamePopup()
{
}

void USB_NewGamePopup::InitFocus()
{
	if (SaveSlots && SaveSlots->GetFirstSlotButton())
	{
		SaveSlots->GetFirstSlotButton()->SetFocus();
	}
}

void USB_NewGamePopup::NativeConstruct()
{
	Super::NativeConstruct();
}

void USB_NewGamePopup::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	SaveSlots->OnClickAction.AddUObject(this, &USB_NewGamePopup::OnClickAction);
	
	if (UGameInstance* GI = GetGameInstance())
	{
		SaveSubsystem = GI->GetSubsystem<USB_SaveLoadSubsystem>();
		LevelTransitionSubsystem = GI->GetSubsystem<USB_LevelTransitionSubsystem>();
	}
}

UWidget* USB_NewGamePopup::NativeGetDesiredFocusTarget() const
{
	if (SaveSlots)
	{
		return SaveSlots->GetFirstSlotButton();
	}
    
	return Super::NativeGetDesiredFocusTarget();
}

void USB_NewGamePopup::OnClickAction(int Index)
{
	if (!SaveSubsystem || !LevelTransitionSubsystem) { return; }
	SaveSubsystem->SaveGameToSlot(Index);
	LevelTransitionSubsystem->MoveToGameLevel();
}