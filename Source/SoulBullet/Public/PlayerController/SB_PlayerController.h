// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SB_PlayerController.generated.h"

class UInputMappingContext;

UENUM(BlueprintType)
enum class EInputMode : uint8
{
	InGame,
	UIOnly
};

UCLASS()
class SOULBULLET_API ASB_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(BlueprintCallable)
	void SettingInputMode(EInputMode InputMode);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;
};
