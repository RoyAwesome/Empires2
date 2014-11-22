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
	GENERATED_UCLASS_BODY()

   //General Usage
public:
		
		virtual UWorld* GetWorld() const override;

		UFUNCTION(BlueprintCallable, Category=Firemode)
		virtual ABaseEmpiresWeapon* GetWeapon();
protected:

	UPROPERTY()
	ABaseEmpiresWeapon* Weapon;


	//FIRE CONTROL
public:
		
	/* Start the firing sequence. */
	virtual void BeginFire();	
	
	/* End the firing sequence */
	virtual void EndFire();

	//Actually Fire the bullet
	virtual void HandleFire();

	virtual bool CanFire()
	{
		return true;
	}

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "Begin Fire"))
	void BTBeginFire();
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "End Fire"))
	void BTEndFire();
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "Handle Fire"))
	void BTHandleFire();

	//TODO: Allow this function to control when something can fire
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "Can Fire"))
	bool BTCanFire();
	
	
	UFUNCTION(BlueprintCallable, Category = Firemode)
		bool IsFiring();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Firemode)
	float BeginFireTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Firemode)
	bool bFiring;

};
