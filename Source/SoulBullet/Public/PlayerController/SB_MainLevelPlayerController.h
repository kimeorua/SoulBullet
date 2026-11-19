// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SB_MainLevelPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class SOULBULLET_API ASB_MainLevelPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputMappingContext> MenuInputMappingContext;
};