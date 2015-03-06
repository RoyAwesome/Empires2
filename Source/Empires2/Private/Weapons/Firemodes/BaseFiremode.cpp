// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "EmpBaseWeapon.h"
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

AEmpBaseWeapon* UBaseFiremode::GetWeapon()
{
	return Cast<AEmpBaseWeapon>(GetOuter());
}

bool UBaseFiremode::IsFiring()
{
	return bFiring;	
}

bool UBaseFiremode::CanFire()
{
	return true && BPCanFire();
}

