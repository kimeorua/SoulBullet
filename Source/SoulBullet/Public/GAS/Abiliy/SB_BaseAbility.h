// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SB_BaseAbility.generated.h"

class ASB_BaseCharacter;
class UCharacterMovementComponent;
class USB_AbilitySystemComponent;

UCLASS()
class SOULBULLET_API USB_BaseAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	USB_BaseAbility();
	
	UFUNCTION(BlueprintPure, Category = "SB|Ability")
	ASB_BaseCharacter* GetBaseCharacterFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "SB|Ability")
	USB_AbilitySystemComponent* GetSBAbilitySystemComponentFromActorInfo() const;
};
