// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Main/SB_BasePopupUI.h"
#include "SB_BaseSaveSlot.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(OnClickActionDelegate, int32);

class UCommonButtonBase;
class UTextBlock;
class USB_SaveLoadSubsystem;

UCLASS()
class SOULBULLET_API USB_BaseSaveSlot : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	USB_BaseSaveSlot();
	
	UFUNCTION()
	void OnClickSaveSlot01();
	
	UFUNCTION()
	void OnClickSaveSlot02();
	
	UFUNCTION()
	void OnClickSaveSlot03();
	
	OnClickActionDelegate OnClickAction;
	
	UCommonButtonBase* GetFirstSlotButton() const { return SaveSlotButton_01; }
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
private:
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SaveSlotButton_01;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SaveSlotButton_02;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SaveSlotButton_03;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> SaveSlotText_01;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> SaveSlotText_02;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> SaveSlotText_03;
	
	UPROPERTY()
	TObjectPtr<USB_SaveLoadSubsystem> SaveSubsystem;
	
	UPROPERTY()
	TArray<UTextBlock*> SaveSlotTexts;
	
	void InitSlotText();
};