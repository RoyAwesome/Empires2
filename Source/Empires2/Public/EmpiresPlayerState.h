// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "EmpiresPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class EMPIRES2_API AEmpiresPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()


public:
	virtual void PostInitializeComponents() override;

	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

	UPROPERTY(Replicated)
	class UBaseEmpiresInventory* Inventory;

	UPROPERTY(EditDefaultsOnly, Category = Class)
	TAssetPtr<class UInfantryClass> DefaultClass;

	UPROPERTY(Replicated)
	TAssetPtr<UInfantryClass> CurrentClass;

public:
	/* Class Selection */
	virtual void SelectClass(TAssetPtr<UInfantryClass> Class);

	//TODO: RequestClassChange


};
