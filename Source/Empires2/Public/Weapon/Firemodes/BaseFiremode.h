// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BaseFiremode.generated.h"

/**
 * Base class for all firemodes.
 * A weapon is a collection of fire modes.  A fire mode defines the way that a weapon fires and handles all of the behaviors of the weapon
 */
UCLASS(Abstract, Blueprintable)
class EMPIRES2_API UBaseFiremode : public UObject
{
	GENERATED_BODY()

		//General Usage
public:
	UBaseFiremode();


	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable, Category = Firemode)
		virtual ABaseEmpiresWeapon* GetWeapon();
protected:


	//FIRE CONTROL
public:

	/* Start the firing sequence. */
	UFUNCTION(BlueprintCallable, Category = "Fire Mode")
	virtual void BeginFire();

	/* End the firing sequence */
	UFUNCTION(BlueprintCallable, Category = "Fire Mode")
	virtual void EndFire();

	//Actually Fire the bullet
	UFUNCTION(BlueprintCallable, Category = "Fire Mode")
	virtual void HandleFire();

	virtual bool CanFire();

	//Handle the start of firing
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "Begin Fire Event"))
		void BPBeginFire();
	//Handle the end of firing (when the player releases the fire key)
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "End Fire Event"))
		void BPEndFire();
	//handle the act of firing
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "Handle Fire Event"))
		void BPHandleFire();

	//Controls if this firemode can fire
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "Can Fire"))
		bool BPCanFire();


	UFUNCTION(BlueprintCallable, Category = Firemode)
		bool IsFiring();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Firemode)
		float BeginFireTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Firemode)
		bool bFiring;

};
