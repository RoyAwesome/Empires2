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

	BPBeginFire();

}
void UBaseFiremode::EndFire()
{
	BPEndFire();
	bFiring = false;

}

void UBaseFiremode::HandleFire()
{
	BPHandleFire();
}

ABaseEmpiresWeapon* UBaseFiremode::GetWeapon()
{
	return Cast<ABaseEmpiresWeapon>(GetOuter());
}

bool UBaseFiremode::IsFiring()
{
	return bFiring;	
}

bool UBaseFiremode::CanFire()
{
	return true && BPCanFire();
}

