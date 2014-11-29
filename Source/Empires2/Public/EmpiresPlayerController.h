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
	
protected:

	

};
