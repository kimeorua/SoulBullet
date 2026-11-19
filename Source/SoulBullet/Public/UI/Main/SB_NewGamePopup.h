// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Main/SB_BasePopupUI.h"
#include "SB_NewGamePopup.generated.h"

class USB_BaseSaveSlot;
class USB_SaveLoadSubsystem;
class USB_LevelTransitionSubsystem;

UCLASS()
class SOULBULLET_API USB_NewGamePopup : public USB_BasePopupUI
{
	GENERATED_BODY()
public:
	USB_NewGamePopup();
	
	virtual void InitFocus() override;
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USB_BaseSaveSlot> SaveSlots;
	
	void OnClickAction(int Index);
	
	UPROPERTY()
	TObjectPtr<USB_SaveLoadSubsystem> SaveSubsystem;
	
	UPROPERTY()
	TObjectPtr<USB_LevelTransitionSubsystem> LevelTransitionSubsystem;
};
