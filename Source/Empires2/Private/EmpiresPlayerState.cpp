// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "EmpiresPlayerState.h"
#include "UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "InfantryClass.h"
#include "BaseInfantryWeapon.h"

AEmpiresPlayerState::AEmpiresPlayerState(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bReplicates = true;
}

void AEmpiresPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AEmpiresPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	
	DOREPLIFETIME(AEmpiresPlayerState, RequestedClass);

}


void AEmpiresPlayerState::SelectClass(TAssetPtr<UInfantryClass> Class)
{
	if (Class.IsNull()) return;

}