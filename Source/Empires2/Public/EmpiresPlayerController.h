// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "EmpiresPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EMPIRES2_API AEmpiresPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()


		/*  Death and Respawn   */
public:


	bool CanRespawn();

	
	void DoRespawn();

	UPROPERTY()
	class AEmpiresPlayerStart* WantedSpawn;


	virtual void NotifyWasHit(AController* InstigatedBy, int32 Damage, const FDamageEvent& DamageEvent);

	UFUNCTION(Client, Unreliable)
		void ClientNotifyWasHit(APlayerState* InstigatatedBy, int32 damage, FVector RelHitLocation, TSubclassOf<UDamageType> DamageType);

	virtual void NotifyLandedHit(APawn* Hit);

	UFUNCTION(Client, Unreliable)
	void ClientNotifyLandedHit(APawn* Hit);

	virtual void NotifyDied(AController* InstigatedBy, bool CanRevive);

	UFUNCTION(Client, Unreliable)
	void ClientNotifyDied(APlayerState* InstigatedBy);
	
	virtual void NotifyRevived(AController* InstigatedBy);

	UFUNCTION(Client, Unreliable)
	void ClientNotifyRevived(APlayerState* InstigatedBy);

	
	virtual void NotifyGameStart();

	UFUNCTION(Client, Unreliable)
	void ClientNotifyGameStart();

	virtual void NotifyCharacterSpawned();

	UFUNCTION(Client, Unreliable)
	void ClientNotifyCharacterSpawned();

	UFUNCTION(BlueprintCallable, Category=GameFlow)
	void RequestRespawn();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRequestRespawn();
protected:

	

};
