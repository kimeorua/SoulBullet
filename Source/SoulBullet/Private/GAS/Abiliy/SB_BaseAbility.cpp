// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abiliy/SB_BaseAbility.h"

#include "Character/SB_BaseCharacter.h"
#include "GAS/ASC/SB_AbilitySystemComponent.h"


USB_BaseAbility::USB_BaseAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

ASB_BaseCharacter* USB_BaseAbility::GetBaseCharacterFromActorInfo() const
{
	return Cast<ASB_BaseCharacter>(GetAvatarActorFromActorInfo());
}

USB_AbilitySystemComponent* USB_BaseAbility::GetSBAbilitySystemComponentFromActorInfo() const
{
	return Cast<USB_AbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}
