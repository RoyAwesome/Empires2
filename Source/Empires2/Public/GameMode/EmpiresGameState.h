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
	GENERATED_BODY()

public:

	AEmpiresGameState(const class FObjectInitializer & ObjectInitializer);

	UPROPERTY(Replicated, Config, EditAnywhere, BlueprintReadWrite, Category=Server)
	FString ServerName;

	UPROPERTY(Replicated, Config, EditAnywhere, BlueprintReadWrite, Category = Server)
	FString ServerMOTD;



private:

	
};
