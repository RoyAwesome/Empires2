// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BaseFiremode.generated.h"

/**
 * Base class for all firemodes.  
 * A weapon is a collection of fire modes.  A fire mode defines the way that a weapon fires and handles all of the behaviors of the weapon
 */
UCLASS(Abstract)
class EMPIRES2_API UBaseFiremode : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	
	UFUNCTION(/*Reliable, Server, WithValidation*/)
	virtual void BeginFire();	

	UFUNCTION(/*Reliable, Server, WithValidation*/)
	virtual void EndFire();
	
	//TODO: Implement Blueprint Hooks so designers can create their own firemodes
	/*
	UFUNCTION(BlueprintImplementableEvent, Category=Weapon)
	void BP_BeginFire();

	UFUNCTION(BlueprintImplementableEvent, Category = Weapon)
	void BP_EndFire();
	*/


	virtual void SetWeapon(class UBaseEmpiresWeapon* Weapon);

	UBaseEmpiresWeapon* Weapon;

};
