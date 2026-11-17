// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/SB_OptionPopup.h"

#include "CommonButtonBase.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Subsystem/SB_OptionGameInstanceSubsystem.h"


USB_OptionPopup::USB_OptionPopup()
{
}

void USB_OptionPopup::InitFocus()
{
	if (SoundUpButton)
	{
		SoundUpButton->SetFocus();
	}
}

void USB_OptionPopup::OnClickSoundUpButton()
{
	if (OptionSubsystem)
	{
		float NewVol = OptionSubsystem->GetMasterVolume() + 0.1f;
		OptionSubsystem->SetMasterVolume(NewVol);
			
		SetSoundBarAndText(OptionSubsystem->GetMasterVolume());
	}
}

void USB_OptionPopup::OnClickSoundDawnButton()
{
	if (OptionSubsystem)
	{
		float NewVol = OptionSubsystem->GetMasterVolume() - 0.1f;
		OptionSubsystem->SetMasterVolume(NewVol);
			
		SetSoundBarAndText(OptionSubsystem->GetMasterVolume());
	}
}

void USB_OptionPopup::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (UGameInstance* GI = GetGameInstance())
	{
		OptionSubsystem = GI->GetSubsystem<USB_OptionGameInstanceSubsystem>();
	}
	
	if (OptionSubsystem && SoundBar && SoundText)
	{
		SetSoundBarAndText(OptionSubsystem->GetMasterVolume());
	}
}

void USB_OptionPopup::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (SoundUpButton && SoundDownButton && !bIsButtonBound)
	{
		SoundUpButton->OnClicked().AddUObject(this, &USB_OptionPopup::OnClickSoundUpButton);
		SoundDownButton->OnClicked().AddUObject(this, &USB_OptionPopup::OnClickSoundDawnButton);
		
		bIsButtonBound = true;
	}
}

UWidget* USB_OptionPopup::NativeGetDesiredFocusTarget() const
{
	return SoundUpButton ? SoundUpButton : Super::GetDesiredFocusTarget();
}

void USB_OptionPopup::SetSoundBarAndText(float Percent) const
{
	if (SoundBar)
	{
		SoundBar->SetPercent(Percent);
	}
	if (SoundText)
	{
		int32 VolumePercent = FMath::RoundToInt(Percent * 100.0f);
		FString VolumeString = FString::Printf(TEXT("%d%%"), VolumePercent);
		
		SoundText->SetText(FText::FromString(VolumeString));
	}
}