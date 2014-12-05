// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BaseEmpiresWeapon.h"
#include "BaseFiremode.h"


UBaseFiremode::UBaseFiremode()
{
	
}

UWorld* UBaseFiremode::GetWorld() const
{
	return GetOuter()->GetWorld();
}

void UBaseFiremode::BeginFire()
{	
	BeginFireTime =  GetWorld()->GetTimeSeconds();
	bFiring = true;

	BTBeginFire();

}
void UBaseFiremode::EndFire()
{
	BTEndFire();
	bFiring = false;

}

void UBaseFiremode::HandleFire()
{
	BTHandleFire();
}

ABaseEmpiresWeapon* UBaseFiremode::GetWeapon()
{
	return Cast<ABaseEmpiresWeapon>(GetOuter());
}

bool UBaseFiremode::IsFiring()
{
	return bFiring;	
}

