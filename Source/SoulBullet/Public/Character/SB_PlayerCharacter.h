// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Character/SB_BaseCharacter.h"
#include "InputActionValue.h"
#include "SB_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USB_InputDataAsset;

UCLASS()
class SOULBULLET_API ASB_PlayerCharacter : public ASB_BaseCharacter
{
	GENERATED_BODY()
	
public:
	ASB_PlayerCharacter();
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<USB_InputDataAsset> InputDataAsset;
	
	void InputMove(const FInputActionValue& InputActionValue);
	void InputLook(const FInputActionValue& InputActionValue);
	
	void Input_AbilityInputTagPressed(FGameplayTag InInputTag) const;
	void Input_AbilityInputTagReleased(FGameplayTag InInputTag) const;
};