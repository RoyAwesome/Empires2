// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "EmpiresGameState.generated.h"


/**
 * 
 */
UCLASS()
class EMPIRES2_API AEmpiresGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(Replicated)
	int32 NumTeams;

	UPROPERTY(Replicated, Config, EditAnywhere, BlueprintReadWrite, Category=Server)
	FString ServerName;

	UPROPERTY(Replicated, Config, EditAnywhere, BlueprintReadWrite, Category = Server)
		FString ServerMOTD;



private:

	
};
