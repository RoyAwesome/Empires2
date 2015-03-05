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
	GENERATED_BODY()


		/*  Death and Respawn   */
public:
	AEmpiresPlayerController(const class FObjectInitializer & ObjectInitializer);

	bool CanRespawn();

	
	void DoRespawn();


	UPROPERTY(BlueprintReadWrite, Category="Controller")
	class AEmpiresPlayerStart* WantedSpawn;


	UFUNCTION(BlueprintCallable, Category = "Empires Player Controller")
	virtual void InitialGameJoin();
	UFUNCTION(BlueprintImplementableEvent, Category = "Empires Player Controller", meta = (FriendlyName = "On Initial Game Join"))
	void BPInitialGameJoin();



	virtual void NotifyWasHit(AController* InstigatedBy, int32 Damage, const FDamageEvent& DamageEvent);

	UFUNCTION(Client, Unreliable)
	void ClientNotifyWasHit(APlayerState* InstigatatedBy, int32 damage, FVector RelHitLocation, TSubclassOf<UDamageType> DamageType);
	void ClientNotifyWasHit_Implementation(APlayerState* InstigatatedBy, int32 damage, FVector RelHitLocation, TSubclassOf<UDamageType> DamageType);

	virtual void NotifyLandedHit(APawn* Hit);

	UFUNCTION(Client, Unreliable)
	void ClientNotifyLandedHit(APawn* Hit);
	void ClientNotifyLandedHit_Implementation(APawn* Hit);

	virtual void NotifyDied(AController* InstigatedBy, bool CanRevive);

	UFUNCTION(Client, Unreliable)
	void ClientNotifyDied(APlayerState* InstigatedBy);
	void ClientNotifyDied_Implementation(APlayerState* InstigatedBy);
	
	virtual void NotifyRevived(AController* InstigatedBy);

	UFUNCTION(Client, Unreliable)
	void ClientNotifyRevived(APlayerState* InstigatedBy);
	void ClientNotifyRevived_Implementation(APlayerState* InstigatedBy);

	
	virtual void NotifyGameStart();

	UFUNCTION(Client, Unreliable)
	void ClientNotifyGameStart();
	void ClientNotifyGameStart_Implementation();

	virtual void NotifyCharacterSpawned();

	UFUNCTION(BlueprintImplementableEvent, Category = "Empires Player Controller", meta=(FriendlyName="Server Character Spawned"))
	void BPServerCharacterSpawned();

	UFUNCTION(Client, Unreliable)
	void ClientNotifyCharacterSpawned();
	void ClientNotifyCharacterSpawned_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Empires Player Controller", meta = (FriendlyName = "Client Character Spawned"))
	void BPClientCharacterSpawned();

	UFUNCTION(BlueprintCallable, Category=GameFlow)
	void RequestRespawn();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRequestRespawn();
	void ServerRequestRespawn_Implementation();
	bool ServerRequestRespawn_Validate();
protected:

	

};
