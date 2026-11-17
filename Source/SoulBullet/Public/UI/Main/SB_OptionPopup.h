// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Main/SB_BasePopupUI.h"
#include "SB_OptionPopup.generated.h"

class UCommonButtonBase;
class UProgressBar;
class UTextBlock;
class USB_OptionGameInstanceSubsystem;

UCLASS()
class SOULBULLET_API USB_OptionPopup : public USB_BasePopupUI
{
	GENERATED_BODY()
public:
	USB_OptionPopup();
	
	virtual void InitFocus() override;
	
	UFUNCTION()
	void OnClickSoundUpButton();
	
	UFUNCTION()
	void OnClickSoundDawnButton();
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SoundUpButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SoundDownButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> SoundBar;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> SoundText;
	
	void SetSoundBarAndText(float Percent) const;
	
	UPROPERTY()
	TObjectPtr<USB_OptionGameInstanceSubsystem> OptionSubsystem;
	
	bool bIsButtonBound = false;
};