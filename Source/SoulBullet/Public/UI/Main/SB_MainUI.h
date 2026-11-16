// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "SB_MainUI.generated.h"

class UCommonActivatableWidgetStack;
class UCommonButtonBase;
class USB_BasePopupUI;

UCLASS()
class SOULBULLET_API USB_MainUI : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	USB_MainUI();
	
	UFUNCTION()
	void OnClickGameStart();
	
protected:
	virtual void NativeConstruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> MenuStack;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> GameStartButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> GameOptionButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> GameQuitButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PopupUI", meta=(AllowPrivateAccess="ture"))
	TSubclassOf<USB_BasePopupUI> GameStartPopupUI;
};
