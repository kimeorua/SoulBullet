// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/SB_GameStartPopup.h"
#include "CommonButtonBase.h"
#include "Subsystem/SB_LevelTransitionSubsystem.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "Subsystem/SB_SaveLoadSubsystem.h"
#include "UI/Main/SB_LoadGamePopupUI.h"
#include "UI/Main/SB_NewGamePopup.h"

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

void USB_GameStartPopup::OnClickNewGame()
{
	UGameInstance* GI = GetGameInstance();
	USB_SaveLoadSubsystem* SaveSubsystem = GI->GetSubsystem<USB_SaveLoadSubsystem>();
	USB_LevelTransitionSubsystem* LevelTransitionSubsystem = GI->GetSubsystem<USB_LevelTransitionSubsystem>();
	
	if (!SaveSubsystem || !LevelTransitionSubsystem) { return; }
	
	if (GI && SaveSubsystem)
	{
		bool bHasAnySaveData = false;
	
		for (int32 i = 1; i <= 3; ++i)
		{
			if (SaveSubsystem->DoesSlotExist(i))
			{
				bHasAnySaveData = true;
				break;
			}
		}
	
		if (bHasAnySaveData)
		{
			if (IsValid(NewGamePopup))
			{
				USB_BasePopupUI* CreatedPopup = SaveSlotStack->AddWidget<USB_BasePopupUI>(NewGamePopup);
		
				if (IsValid(CreatedPopup))
				{
					CreatedPopup->InitFocus();
				}
			}
		}
		else
		{
			SaveSubsystem->SaveGameToSlot(1);
			LevelTransitionSubsystem->MoveToGameLevel();
		}
	}
}

void USB_GameStartPopup::OnClickLoadGame()
{
	if (IsValid(LoadGamePopup))
	{
		USB_BasePopupUI* CreatedPopup = SaveSlotStack->AddWidget<USB_BasePopupUI>(LoadGamePopup);
		
		if (IsValid(CreatedPopup))
		{
			CreatedPopup->InitFocus();
		}
	}
}

void USB_GameStartPopup::NativeConstruct()
{
	Super::NativeConstruct();
	
	UGameInstance* GI = GetGameInstance();
	USB_SaveLoadSubsystem* SaveSubsystem = GI->GetSubsystem<USB_SaveLoadSubsystem>();
	
	if (!SaveSubsystem) { return; }
	
	LoadGameButton->SetIsEnabled(false);
	
	for (int i = 1; i <= 3; i++)
	{
		if (SaveSubsystem->DoesSlotExist(i))
		{
			LoadGameButton->SetIsEnabled(true);
			break;
		}
	}
}

void USB_GameStartPopup::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (NewGameButton)
	{
		NewGameButton->OnClicked().AddUObject(this, &USB_GameStartPopup::OnClickNewGame);
	}
	if (LoadGameButton)
	{
		LoadGameButton->OnClicked().AddUObject(this, &USB_GameStartPopup::OnClickLoadGame);
	}
}

UWidget* USB_GameStartPopup::NativeGetDesiredFocusTarget() const
{
	return NewGameButton ? NewGameButton : Super::NativeGetDesiredFocusTarget();
}