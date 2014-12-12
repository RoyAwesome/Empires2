// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#ifndef __EMPIRES2_H__
#define __EMPIRES2_H__

#include "Engine.h"
#include "Empires2Character.h"
#include "EmpiresPlayerController.h"
#include "Empires2Classes.h"

#define COLLISION_PROJECTILE	ECC_GameTraceChannel1
#define COLLISION_USE			ECC_GameTraceChannel2

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


UENUM()
namespace EEmpiresTeam
{
	enum Type
	{
		Team_Unassigned = 0, //When a player joins, they are naturally Unassigned.  
		Team_BlueTeam = 1, //Usually Brenodi 
		Team_RedTeam = 2, //Usually Northern Faction
		Team_GreenTeam = 3, //Custom Team for special game modes
		Team_YellowTeam = 4, //Custom Team for special game modes
		Team_Spectator = 5,
		Count = 6,
	};
}


#endif
