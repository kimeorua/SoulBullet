// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/SB_BaseSaveSlot.h"

#include "CommonButtonBase.h"
#include "Components/TextBlock.h"
#include "Log/SB_Log.h"
#include "SaveGame/SB_PlayerSaveGame.h"
#include "Subsystem/SB_SaveLoadSubsystem.h"


USB_BaseSaveSlot::USB_BaseSaveSlot()
{
}

void USB_BaseSaveSlot::OnClickSaveSlot01()
{
	OnClickAction.Broadcast(1);
}

void USB_BaseSaveSlot::OnClickSaveSlot02()
{
	OnClickAction.Broadcast(2);
}

void USB_BaseSaveSlot::OnClickSaveSlot03()
{
	OnClickAction.Broadcast(3);
}

void USB_BaseSaveSlot::InitSlotText()
{
	if (!SaveSubsystem)
	{
		SB_Log(LogSBCore, Error, TEXT("SaveSubsystem is NULL"));
		return;
	}
	
	for (int i = 0; i < 3; i++)
	{
		if (SaveSubsystem->LoadGameFromSlot(i + 1))
		{
			FString TextString = FString::Printf(TEXT("Test Int : %d"), SaveSubsystem->GetCurrentSaveGameData()->TestInt);
			SaveSlotTexts[i]->SetText(FText::FromString(TextString));
		}
		else
		{
			SaveSlotTexts[i]->SetText(FText::FromString("Empty"));
		}
	}
}

void USB_BaseSaveSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void USB_BaseSaveSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (SaveSlotButton_01)
	{
		SaveSlotButton_01->OnClicked().AddUObject(this, &USB_BaseSaveSlot::OnClickSaveSlot01);
	}
	
	if (SaveSlotButton_02)
	{
		SaveSlotButton_02->OnClicked().AddUObject(this, &USB_BaseSaveSlot::OnClickSaveSlot02);
	}
	
	if (SaveSlotButton_03)
	{
		SaveSlotButton_03->OnClicked().AddUObject(this, &USB_BaseSaveSlot::OnClickSaveSlot03);
	}
	
	UGameInstance* GI = GetGameInstance();
	SaveSubsystem = GI->GetSubsystem<USB_SaveLoadSubsystem>();
	
	SaveSlotTexts.Empty();
	
	SaveSlotTexts.Add(SaveSlotText_01);
	SaveSlotTexts.Add(SaveSlotText_02);
	SaveSlotTexts.Add(SaveSlotText_03);
}

void USB_BaseSaveSlot::NativeOnActivated()
{
	Super::NativeOnActivated();
	InitSlotText();
}

UWidget* USB_BaseSaveSlot::NativeGetDesiredFocusTarget() const
{
	return SaveSlotButton_01 ? SaveSlotButton_01 : Super::NativeGetDesiredFocusTarget();
}
