// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/SB_BaseSaveSlot.h"

#include "CommonButtonBase.h"


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
}

UWidget* USB_BaseSaveSlot::NativeGetDesiredFocusTarget() const
{
	return SaveSlotButton_01 ? SaveSlotButton_01 : Super::NativeGetDesiredFocusTarget();
}