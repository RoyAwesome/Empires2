// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Empires2.h"
#include "EmpBaseGamemode.h"
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



AEmpBaseGamemode::AEmpBaseGamemode(const class FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	
	// use our custom HUD class
	HUDClass = AEmpires2HUD::StaticClass();

	this->PlayerStateClass = AEmpiresPlayerState::StaticClass();

	bUseSeamlessTravel = true;
}

void AEmpBaseGamemode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	BPInitGame(MapName, Options, ErrorMessage);
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AEmpBaseGamemode::PreLogin(const FString& Options, const FString& Address, const TSharedPtr<class FUniqueNetId>& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

void AEmpBaseGamemode::PostLogin(APlayerController* NewPlayer)
{
	BPPostLogin(NewPlayer);

	Super::PostLogin(NewPlayer); 
	
	AEmpiresPlayerController* PC = Cast<AEmpiresPlayerController>(NewPlayer);
	PC->InitialGameJoin();


}

AActor* AEmpBaseGamemode::ChoosePlayerStart(AController* Player)
{
	AActor* Spawn = BPChoosePlayerStart(Player);
	if (Spawn == nullptr)
	{
		Spawn = Super::ChoosePlayerStart(Player);
	}

	return Spawn;
}

void AEmpBaseGamemode::SetFriendlyFire(bool ShouldFriendlyfire)
{
	bAllowFriendlyFire = ShouldFriendlyfire;
}

bool AEmpBaseGamemode::ShouldSpawnAtStartSpot(AController* Player)
{
	return false;
}

UClass* AEmpBaseGamemode::GetDefaultPawnClassForController(AController* InController)
{
	//TODO: Bots?

	return Super::GetDefaultPawnClassForController(InController);
}

float AEmpBaseGamemode::ModifyDamage(float Damage, AActor* DamagedActor, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const
{	
	//Determine if these two people can deal damage to eachother.  If they can't, change damage to 0 then pass it to Blueprint to modify.
	if (!CanDealDamage(EventInstigator, DamagedActor->GetInstigatorController()))
	{
		Damage = 0;
	}


	Damage = BPModifyDamage(Damage, DamagedActor, DamageEvent, EventInstigator, DamageCauser);
	return Damage;	
}

void AEmpBaseGamemode::Killed(AController* Killer, AController* KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType)
{
	BPKilled(Killer, KilledPlayer, KilledPawn, DamageType);
}

bool AEmpBaseGamemode::CanDealDamage(AController* DamageInstigator, AController* DamagedPlayer) const
{	
	return true || BPCanDealDamage(DamageInstigator, DamagedPlayer);
}

bool AEmpBaseGamemode::AllowCheats(APlayerController* P)
{
	return false;
}

void AEmpBaseGamemode::DefaultTimer()
{
	Super::DefaultTimer();


	if (GetWorld()->IsPlayInEditor())
	{
		return;
	}

	//TODO: Postgame Scoreboard


}

void AEmpBaseGamemode::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();
	BPHandleMatchIsWaitingToStart();
}

void AEmpBaseGamemode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
	BPHandleMatchHasStarted();
}

void AEmpBaseGamemode::RestartGame()
{
	Super::RestartGame();
	BPRestartGame();
}

TSubclassOf<AGameSession> AEmpBaseGamemode::GetGameSessionClass() const
{
	return AGameSession::StaticClass();
}

void AEmpBaseGamemode::FinishMatch()
{

}

void AEmpBaseGamemode::RespawnPlayer(AEmpiresPlayerController* Controller)
{
	BPRespawnPlayer(Controller);
}

void AEmpBaseGamemode::BPRespawnPlayer_Implementation(AEmpiresPlayerController* Controller)
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

void AEmpBaseGamemode::NotifyDamageWasDealt(AController* DamageInstigator, AActor* WithWhat, AController* DamagedPlayer, AActor* DamagedActor, float Amount, struct FDamageEvent const& DamageEvent)
{
	BPNotifyDamageWasDealt(DamageInstigator, WithWhat, DamagedPlayer, DamagedActor, Amount, DamageEvent);
}
