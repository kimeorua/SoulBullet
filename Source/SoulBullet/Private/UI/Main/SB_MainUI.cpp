// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Main/SB_MainUI.h"

#include "CommonButtonBase.h"
#include "Kismet/GameplayStatics.h"
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

void USB_MainUI::OnClickOption()
{
	if (IsValid(GameStartPopupUI))
	{
		USB_BasePopupUI* CreatedPopup = MenuStack->AddWidget<USB_BasePopupUI>(GameOptionPopupUI);
		
		if (IsValid(CreatedPopup))
		{
			CreatedPopup->InitFocus();
		}
	}
}

void USB_MainUI::OnClickQuit()
{
	APlayerController* PC = nullptr;
	if (ULocalPlayer* LocalPlayer = GetOwningLocalPlayer())
	{
		PC = LocalPlayer->GetPlayerController(GetWorld());
	}
	
	UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, false);
}

void USB_MainUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (GameStartButton)
	{
		GameStartButton->SetFocus();
		
		GameStartButton->OnClicked().AddUObject(this, &USB_MainUI::OnClickGameStart);
	}
	
	if (GameOptionButton)
	{
		GameOptionButton->OnClicked().AddUObject(this, &USB_MainUI::OnClickOption);
	}
	
	if (GameQuitButton)
	{
		GameQuitButton->OnClicked().AddUObject(this, &USB_MainUI::OnClickQuit);
	}
}

UWidget* USB_MainUI::NativeGetDesiredFocusTarget() const
{
	return GameStartButton ? GameStartButton : Super::NativeGetDesiredFocusTarget();
}