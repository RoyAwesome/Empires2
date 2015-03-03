// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Empires2.h"
#include "Empires2GameMode.h"
#include "Empires2HUD.h"
#include "Empires2Character.h"
#include "EmpiresPlayerState.h"
#include "EmpiresPlayerController.h"
#include "EmpiresPlayerStart.h"

namespace MatchState
{
	
	const FName PregameVote = FName(TEXT("PregameVote"));
	const FName PostGame = FName(TEXT("PostGame"));
	const FName PostGameVoting = FName(TEXT("PostgameVote"));
}



AEmpires2GameMode::AEmpires2GameMode(const class FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/EmpiresCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AEmpires2HUD::StaticClass();

	this->PlayerStateClass = AEmpiresPlayerState::StaticClass();

	bUseSeamlessTravel = true;
}

void AEmpires2GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	BPInitGame(MapName, Options, ErrorMessage);
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AEmpires2GameMode::PreLogin(const FString& Options, const FString& Address, const TSharedPtr<class FUniqueNetId>& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

void AEmpires2GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer); 

	BPPostLogin(NewPlayer);

	//TODO: Get a spawn point for the player
}

AActor* AEmpires2GameMode::ChoosePlayerStart(AController* Player)
{
	AActor* Spawn = BPChoosePlayerStart(Player);
	if (Spawn == nullptr)
	{
		Spawn = Super::ChoosePlayerStart(Player);
	}

	return Spawn;
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
	//Determine if these two people can deal damage to eachother.  If they can't, change damage to 0 then pass it to Blueprint to modify.
	if (!CanDealDamage(EventInstigator, DamagedActor->GetInstigatorController()))
	{
		Damage = 0;
	}


	Damage = BPModifyDamage(Damage, DamagedActor, DamageEvent, EventInstigator, DamageCauser);
	return Damage;	
}

void AEmpires2GameMode::Killed(AController* Killer, AController* KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType)
{
	BPKilled(Killer, KilledPlayer, KilledPawn, DamageType);
}

bool AEmpires2GameMode::CanDealDamage(AController* DamageInstigator, AController* DamagedPlayer) const
{	
	return true || BPCanDealDamage(DamageInstigator, DamagedPlayer);
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
	Super::HandleMatchIsWaitingToStart();
	BPHandleMatchIsWaitingToStart();
}

void AEmpires2GameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
	BPHandleMatchHasStarted();
}

void AEmpires2GameMode::RestartGame()
{
	Super::RestartGame();
	BPRestartGame();
}

TSubclassOf<AGameSession> AEmpires2GameMode::GetGameSessionClass() const
{
	return AGameSession::StaticClass();
}

void AEmpires2GameMode::FinishMatch()
{

}

void AEmpires2GameMode::RespawnPlayer(AEmpiresPlayerController* Controller)
{
	BPRespawnPlayer(Controller);
}

void AEmpires2GameMode::BPRespawnPlayer_Implementation(AEmpiresPlayerController* Controller)
{
	//Remove the player's original pawn
	AEmpires2Character* PlayerCharacter = Cast<AEmpires2Character>(Controller->GetPawn());

	PlayerCharacter->Respawn();


	//Create a new pawn for the player
	AActor* StartSpot = ChoosePlayerStart(Controller);
	if (StartSpot == nullptr)
	{
		UE_LOG(EmpiresGameplay, Warning, TEXT("Can't find a spawn for player"));
	}

	APawn* Pawn = this->SpawnDefaultPawnFor(Controller, StartSpot);

	Controller->Possess(Pawn);
	Controller->NotifyCharacterSpawned();
}
