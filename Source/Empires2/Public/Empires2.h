// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#ifndef __EMPIRES2_H__
#define __EMPIRES2_H__

#include "Engine.h"
#include "Empires2Character.h"
#include "Empires2Classes.h"

#define COLLISION_PROJECTILE	ECC_GameTraceChannel1

DECLARE_LOG_CATEGORY_EXTERN(EmpiresGameplay, Display, All);
DECLARE_LOG_CATEGORY_EXTERN(EmpiresNetwork, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Empires, Log, All);

#define SCREENLOG(text, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, FString::Printf__VA(TEXT("[%s:%d] %s"), TEXT(__FUNCTION__), __LINE__, *FString::Printf__VA(text, ##__VA_ARGS__)))

#define NETMODE_WORLD (((GEngine == NULL) || (GetWorld() == NULL)) ? TEXT("") \
        : (GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
        : (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
        : (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
        : TEXT("[Standalone] "))

#if _MSC_VER
#define FUNC_NAME    TEXT(__FUNCTION__)
#else // FIXME - GCC?
#define FUNC_NAME    TEXT(__func__)
#endif

#define TRACE(Format, ...) \
{ \
    SET_WARN_COLOR( COLOR_CYAN );\
    FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__ ); \
    UE_LOG( Empires, Log, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg);\
    CLEAR_WARN_COLOR();\
}


#endif
