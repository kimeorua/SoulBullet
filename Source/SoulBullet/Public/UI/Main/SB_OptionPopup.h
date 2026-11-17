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
	
	UFUNCTION()
	void OnClickGraphicUpButton();
	
	UFUNCTION()
	void OnClickGraphicDownButton();
	
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
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> GraphicUpButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> GraphicDownButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> GraphicText;
	
	int GraphicLevel = 3;
	
	void SetSoundBarAndText(float Percent) const;
	void SetGraphicText(int32 InGraphicLevel);
	
	UPROPERTY()
	TObjectPtr<USB_OptionGameInstanceSubsystem> OptionSubsystem;
	
	bool bIsButtonBound = false;
};