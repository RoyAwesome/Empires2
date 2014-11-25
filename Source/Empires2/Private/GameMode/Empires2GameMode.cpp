// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Empires2.h"
#include "Empires2GameMode.h"
#include "Empires2HUD.h"
#include "Empires2Character.h"
#include "EmpiresPlayerState.h"

namespace MatchState
{
	
	const FName PregameVote = FName(TEXT("PregameVote"));
	const FName PostGame = FName(TEXT("PostGame"));
	const FName PostGameVoting = FName(TEXT("PostgameVote"));
}



AEmpires2GameMode::AEmpires2GameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/EmpiresCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AEmpires2HUD::StaticClass();

	this->PlayerStateClass = AEmpiresPlayerState::StaticClass();
}

void AEmpires2GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AEmpires2GameMode::PreLogin(const FString& Options, const FString& Address, const TSharedPtr<class FUniqueNetId>& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

void AEmpires2GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer); 

	//TODO: Get a spawn point for the player
}

AActor* AEmpires2GameMode::ChoosePlayerStart(AController* Player)
{
	return Super::ChoosePlayerStart(Player); 

	//Get the spawn point that this player requested.  
}

void AEmpires2GameMode::SetFriendlyFire(bool ShouldFriendlyfire)
{
	bAllowFriendlyFire = ShouldFriendlyfire;
}

bool AEmpires2GameMode::ShouldSpawnAtStartSpot(AController* Player)
{
	return false;
}

UClass* AEmpires2GameMode::GetDefaultPawnClassForController(AController* InController)
{
	//TODO: Bots?

	return Super::GetDefaultPawnClassForController(InController);
}

float AEmpires2GameMode::ModifyDamage(float Damage, AActor* DamagedActor, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const
{
	return Damage;

	//TODO: Determine if the people are on the same team.  If they are, Prevent that damage.  If not allow it
}

void AEmpires2GameMode::Killed(AController* Killer, AController* KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType)
{

}

bool AEmpires2GameMode::CanDealDamage(class AEmpiresPlayerState* DamageInstigator, class AEmpiresPlayerState* DamagedPlayer) const
{
	//TODO: Friendly Fire? 
	return true;
}

bool AEmpires2GameMode::AllowCheats(APlayerController* P)
{
	return false;
}

void AEmpires2GameMode::DefaultTimer()
{
	Super::DefaultTimer();


	if (GetWorld()->IsPlayInEditor())
	{
		return;
	}

	//TODO: Postgame Scoreboard


}

void AEmpires2GameMode::HandleMatchIsWaitingToStart()
{

}

void AEmpires2GameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
}

void AEmpires2GameMode::RestartGame()
{
	Super::RestartGame();
}

TSubclassOf<AGameSession> AEmpires2GameMode::GetGameSessionClass() const
{
	return AGameSession::StaticClass();
}

void AEmpires2GameMode::FinishMatch()
{

}
