// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "EmpBaseGamemode.generated.h"



/*
GAME STATES
-Waiting To Start (Engine): The period of time when everyone is loading in to the map
-PregameVote: Used in some game modes where a pregame vote is required, such as selecting a commander or game properties (#flags in CTF, etc)
-InProgress (Engine): Game is playing
-PostGame: One team has won the game.  Show the scoreboard.
-PostGameVoting: Select Next Map/Mode
*/
namespace MatchState
{
	extern EMPIRES2_API const FName PregameVote;
	extern EMPIRES2_API const FName PostGame;
	extern EMPIRES2_API const FName PostGameVoting;
}


UCLASS(minimalapi)
class AEmpBaseGamemode : public AGameMode
{
	GENERATED_BODY()

public:
	AEmpBaseGamemode(const class FObjectInitializer & ObjectInitializer);


	/** Initialize the game. This is called before actors' PreInitializeComponents. */
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode", meta=(FriendlyName = "Init Game"))
	void BPInitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

	/** Accept or reject a player attempting to join the server.  Fails login if you set the ErrorMessage to a non-empty string. */
	virtual void PreLogin(const FString& Options, const FString& Address, const TSharedPtr<class FUniqueNetId>& UniqueId, FString& ErrorMessage) override;

	/** starts match warmup */	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	//Handle player entering the world
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode", meta = (FriendlyName = "Post Login"))
	void BPPostLogin(APlayerController* NewPlayer);

	/** select best spawn point for player */
	virtual AActor* ChoosePlayerStart(AController* Player) override;

	//Handle spawn point selection
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode", meta = (FriendlyName = "Choose Player Start"))
	AActor* BPChoosePlayerStart(AController* Player);


	/** always pick new random spawn */
	virtual bool ShouldSpawnAtStartSpot(AController* Player) override;

	/** returns default pawn class for given controller */
	virtual UClass* GetDefaultPawnClassForController(AController* InController) override;

	/** prevents friendly fire */
	virtual float ModifyDamage(float Damage, AActor* DamagedActor, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const;

	//Modify the amount of damage being dealt to a player.
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode", meta = (FriendlyName = "Modify Damage"))
	float BPModifyDamage(float Damage, AActor* DamagedActor, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const;



	/** notify about kills */
	virtual void Killed(AController* Killer, AController* KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType);
	
	//Handle the death of a player
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode", meta = (FriendlyName = "Killed"))
	void BPKilled(AController* Killer, AController* KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType);

	/** can players damage each other? */
	virtual bool CanDealDamage(class AController* DamageInstigator, class AController* DamagedPlayer) const;

	//Determine if two players can damage eachother
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode", meta = (FriendlyName = "Can Deal Damage"))
		bool BPCanDealDamage(class AController* DamageInstigator, class AController* DamagedPlayer) const;


	virtual void NotifyDamageWasDealt(AController* DamageInstigator, AActor* WithWhat, AController* DamagedPlayer, AActor* DamagedActor, float Amount, struct FDamageEvent const& DamageEvent);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode", meta = (FriendlyName = "Damage Was Dealt"))
		void BPNotifyDamageWasDealt(AController* DamageInstigator, AActor* WithWhat, AController* DamagedPlayer, AActor* DamagedActor, float Amount, struct FDamageEvent const& DamageEvent);
	


	/** always create cheat manager */
	virtual bool AllowCheats(APlayerController* P) override;

	/** update remaining time */
	virtual void DefaultTimer() override;

	/** called before startmatch */
	virtual void HandleMatchIsWaitingToStart() override;

	//Handle pre-match setup.  
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode", meta = (FriendlyName = "Match is Waiting to Start"))
	void BPHandleMatchIsWaitingToStart();


	/** starts new match */
	virtual void HandleMatchHasStarted() override;

	//Event fired when the match starts and all players spawn in
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode", meta = (FriendlyName = "Match Start"))
	void BPHandleMatchHasStarted();

	/** hides the onscreen hud and restarts the map */
	virtual void RestartGame() override;

	//Handle restarting the game.  This resets everything back to the start of the match
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode", meta = (FriendlyName = "Restart match"))
	void BPRestartGame();

	/*  */
	
	virtual void RespawnPlayer(class AEmpiresPlayerController* Controller);

	//Handle the respawning of a player.  You should not need to implement this unless you are completly redoing the native respawn code
	UFUNCTION(BlueprintNativeEvent, Category = "Game Mode", meta = (FriendlyName = "Respawn Player"))
	void BPRespawnPlayer(AEmpiresPlayerController* Controller);
	void BPRespawnPlayer_Implementation(AEmpiresPlayerController* Controller);

protected:

	/** score for kill */
	UPROPERTY(config)
		int32 KillScore;

	/** scale for self instigated damage */
	UPROPERTY(config)
		float DamageSelfScale;

	/** How long the end match time is before the server travels to the next map */
	UPROPERTY(config)
	float EndMatchTime;

	UPROPERTY(config)
		bool bAllowFriendlyFire;

	/** Returns game session class to use */
	virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;

	UPROPERTY(EditDefaultsOnly, Category=GameFlow)
	float PregameVoteTime;

	UPROPERTY(EditDefaultsOnly, Category = GameFlow)
	float PostgameVoteTime;

	/* How long each match takes.  MatchTime <=0 means infinite time */
	UPROPERTY(EditDefaultsOnly, Category = GameFlow)
	float MatchTime; 


public:

	/** finish current match and lock players */
	UFUNCTION(exec)
		void FinishMatch();

	void SetFriendlyFire(bool ShouldFriendlyfire);


};



