// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "InfantryInventory.h"
#include "EmpiresPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class EMPIRES2_API AEmpiresPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()


public:
	
	//The inventory we want
	FInfantryInventory Inventory;
};
