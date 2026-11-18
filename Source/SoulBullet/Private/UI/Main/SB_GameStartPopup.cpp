// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/SB_GameStartPopup.h"
#include "CommonButtonBase.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "Subsystem/SB_SaveLoadSubsystem.h"
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
			SaveSubsystem->SaveGameToSlot_Menu(1);
		}
	}
}

void USB_GameStartPopup::NativeConstruct()
{
	Super::NativeConstruct();
}

void USB_GameStartPopup::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (NewGameButton)
	{
		NewGameButton->OnClicked().AddUObject(this, &USB_GameStartPopup::OnClickNewGame);
	}
}

UWidget* USB_GameStartPopup::NativeGetDesiredFocusTarget() const
{
	return NewGameButton ? NewGameButton : Super::NativeGetDesiredFocusTarget();
}