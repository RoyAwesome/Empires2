// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "EmpInfantryClass.h"
#include "EmpiresPlayerState.generated.h"

/**
 *
 */
UCLASS()
class EMPIRES2_API AEmpiresPlayerState : public APlayerState
{
	GENERATED_BODY()


public:
	AEmpiresPlayerState(const class FObjectInitializer & ObjectInitializer);

	virtual void PostInitializeComponents() override;




	UPROPERTY(EditDefaultsOnly, Category = Class)
	class UEmpInfantryClass* DefaultClass;

	UPROPERTY(Replicated)
	UEmpInfantryClass* RequestedClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Class)
	struct FEmpClassLoadout RequestedLoadout;
	

public:
	/* Class Selection */
	virtual void SelectClass(TAssetPtr<UEmpInfantryClass> Class);

	//TODO: RequestClassChange


	/*  SPAWN SELECTION  */
public:
	UPROPERTY()
	class AEmpiresPlayerStart* WantedSpawn;



};
