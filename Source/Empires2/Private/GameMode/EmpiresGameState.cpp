// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "EmpiresGameState.h"
#include "UnrealNetwork.h"


AEmpiresGameState::AEmpiresGameState(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


void AEmpiresGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AEmpiresGameState, NumTeams, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(AEmpiresGameState, ServerName, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(AEmpiresGameState, ServerMOTD, COND_InitialOnly);
		
}
