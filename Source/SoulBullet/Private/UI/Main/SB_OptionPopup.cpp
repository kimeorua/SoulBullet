// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/SB_OptionPopup.h"

#include "CommonButtonBase.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Log/SB_Log.h"
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

void USB_OptionPopup::OnClickGraphicUpButton()
{
	if (OptionSubsystem)
	{
		int32 CurrentQuality = OptionSubsystem->GetGraphicQuality();
		OptionSubsystem->SetGraphicQuality(CurrentQuality + 1);
		SetGraphicText(OptionSubsystem->GetGraphicQuality());
	}
}

void USB_OptionPopup::OnClickGraphicDownButton()
{
	if (OptionSubsystem)
	{
		int32 CurrentQuality = OptionSubsystem->GetGraphicQuality();
		OptionSubsystem->SetGraphicQuality(CurrentQuality - 1);
		SetGraphicText(OptionSubsystem->GetGraphicQuality());
	}
}

void USB_OptionPopup::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (UGameInstance* GI = GetGameInstance())
	{
		OptionSubsystem = GI->GetSubsystem<USB_OptionGameInstanceSubsystem>();
	}
	
	if (OptionSubsystem)
	{
		if (SoundBar && SoundText)
		{
			SetSoundBarAndText(OptionSubsystem->GetMasterVolume());
		}
		if (SoundText)
		{
			SetGraphicText(OptionSubsystem->GetGraphicQuality());
		}
	}
}

void USB_OptionPopup::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (!bIsButtonBound)
	{
		if (SoundUpButton && SoundDownButton)
		{
			SoundUpButton->OnClicked().AddUObject(this, &USB_OptionPopup::OnClickSoundUpButton);
			SoundDownButton->OnClicked().AddUObject(this, &USB_OptionPopup::OnClickSoundDawnButton);
		}
		if (GraphicUpButton && GraphicDownButton && !bIsButtonBound)
		{
			GraphicUpButton->OnClicked().AddUObject(this, &USB_OptionPopup::OnClickGraphicUpButton);
			GraphicDownButton->OnClicked().AddUObject(this, &USB_OptionPopup::OnClickGraphicDownButton);
		}
		
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

void USB_OptionPopup::SetGraphicText(int32 InGraphicLevel)
{
	switch (InGraphicLevel)
	{
	case 0 :
		GraphicText->SetText(FText::FromString("Low"));
		break;
	case 1 :
		GraphicText->SetText(FText::FromString("Medium"));
		break;
	case 2 :
		GraphicText->SetText(FText::FromString("High"));
		break;
	case 3 :
		GraphicText->SetText(FText::FromString("Epic"));
		break;
	case 4 :
		GraphicText->SetText(FText::FromString("Cinematic"));
		break;
	}
}
