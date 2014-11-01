// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#ifndef __EMPIRES2_H__
#define __EMPIRES2_H__

#include "EngineMinimal.h"
#include "Empires2Character.h"

#define COLLISION_PROJECTILE	ECC_GameTraceChannel1

DECLARE_LOG_CATEGORY_EXTERN(EmpiresGameplay, Display, All);
DECLARE_LOG_CATEGORY_EXTERN(EmpiresNetwork, Log, All);

#define SCREENLOG(text, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, FString::Printf__VA(text, ##__VA_ARGS__))


#endif
