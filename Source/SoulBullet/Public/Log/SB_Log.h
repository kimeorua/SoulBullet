// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/** 전투 및 히트 판정, 데미지 연산 관련 로그 카테고리 */
DECLARE_LOG_CATEGORY_EXTERN(LogSBCombat, Log, All);
/** GAS 관련 로그 */
DECLARE_LOG_CATEGORY_EXTERN(LogSBAbility, Log, All);
/** DataAsset 관련 로그 */
DECLARE_LOG_CATEGORY_EXTERN(LogSBData, Log, All); 
/** 캐릭터 및 Component 관련 로그 */
DECLARE_LOG_CATEGORY_EXTERN(LogSBCharacter , Log, All);
/** 게임 모드, 세이브/로드 등 전역 시스템 관련 로그 */
DECLARE_LOG_CATEGORY_EXTERN(LogSBCore , Log, All);

#define SB_Log(Category, Verbosity, Format, ...)\
	UE_LOG(Category, Verbosity, TEXT("[%s] " Format), *FString(__FUNCTION__), ##__VA_ARGS__);