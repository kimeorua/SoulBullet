// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SB_MainLevelGameMode.h"

#include "PlayerController/SB_MainLevelPlayerController.h"


ASB_MainLevelGameMode::ASB_MainLevelGameMode()
{
	DefaultPawnClass = APawn::StaticClass();
	PlayerControllerClass = ASB_MainLevelPlayerController::StaticClass();
}