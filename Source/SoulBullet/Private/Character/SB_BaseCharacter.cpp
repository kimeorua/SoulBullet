// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SB_BaseCharacter.h"

#include "GAS/ASC/SB_AbilitySystemComponent.h"
#include "Log/SB_Log.h"

ASB_BaseCharacter::ASB_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SB_ASC = CreateDefaultSubobject<USB_AbilitySystemComponent>(TEXT("SB_ASC"));
}

UAbilitySystemComponent* ASB_BaseCharacter::GetAbilitySystemComponent() const
{
	return SB_ASC;
}

void ASB_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASB_BaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (! SB_ASC)
	{
		SB_Log(LogSBAbility, Warning, TEXT("SB_ASC Is Not Valid"));
		return;
	}
	SB_ASC->InitAbilityActorInfo(this, this);
}