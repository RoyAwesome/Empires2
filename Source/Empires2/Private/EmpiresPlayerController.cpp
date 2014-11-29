// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "Empires2GameMode.h"
#include "EmpiresPlayerController.h"
#include "Empires2HUD.h"


AEmpiresPlayerController::AEmpiresPlayerController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

bool AEmpiresPlayerController::CanRespawn()
{
	AEmpires2Character* Character = Cast<AEmpires2Character>(GetPawn());

	if (!Character->bIsDead) return false;

	if (GetWorld()->TimeSince(Character->LastDeathTime) >= 10.0f) return true;

	return false;
}

void AEmpiresPlayerController::DoRespawn()
{
	if (Role != ROLE_Authority) return;

	AEmpires2Character* Character = Cast<AEmpires2Character>(GetPawn());

	UnPossess(); //Unposses our character

	//Destroy it
	Character->Respawn();

	//Request from the game mode that we want to respawn
	AEmpires2GameMode* GameMode = Cast<AEmpires2GameMode>(GetWorld()->GetAuthGameMode());

	GameMode->RespawnPlayer(this);
	
}

void AEmpiresPlayerController::NotifyWasHit(AController* InstigatedBy, int32 Damage, const FDamageEvent& DamageEvent)
{
	APlayerState* InstigatedByState = (InstigatedBy != nullptr) ?  InstigatedBy->PlayerState : nullptr;

	FVector HitLocation(FVector::ZeroVector);

	//TODO: Get the location of the damage

	ClientNotifyWasHit(InstigatedByState, Damage, HitLocation, DamageEvent.DamageTypeClass);

}

void AEmpiresPlayerController::ClientNotifyWasHit_Implementation(APlayerState* InstigatatedBy, int32 damage, FVector RelHitLocation, TSubclassOf<UDamageType> DamageType)
{
	//Play something on the hud when we've been damaged
	if (this->MyHUD)
	{
		AEmpires2HUD* Emp2Hud = Cast<AEmpires2HUD>(MyHUD);
		
		//Notify that we've taken damage
		Emp2Hud->NotifyTookDamage(RelHitLocation, damage, InstigatatedBy);
	}
}


