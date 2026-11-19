// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Main/SB_BasePopupUI.h"
#include "SB_GameStartPopup.generated.h"

class UCommonButtonBase;
class USB_NewGamePopup;
class USB_LoadGamePopupUI;
class UCommonActivatableWidgetStack;

UCLASS()
class SOULBULLET_API USB_GameStartPopup : public USB_BasePopupUI
{
	GENERATED_BODY()
	
public:
	USB_GameStartPopup();
	
	virtual void InitFocus() override;
	
	UFUNCTION()
	void OnClickNewGame();
	
	UFUNCTION()
	void OnClickLoadGame();
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> NewGameButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> LoadGameButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> SaveSlotStack;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Popup Class", meta=(AllowPrivateAccess="true"))
	TSubclassOf<USB_NewGamePopup> NewGamePopup;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Popup Class", meta=(AllowPrivateAccess="true"))
	TSubclassOf<USB_LoadGamePopupUI> LoadGamePopup;
};