// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BaseEmpiresWeapon.h"
#include "BaseFiremode.h"


UBaseFiremode::UBaseFiremode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


void UBaseFiremode::BeginFire()
{

}
void UBaseFiremode::EndFire()
{

}
void UBaseFiremode::SetWeapon(UBaseEmpiresWeapon* Weapon)
{
	this->Weapon = Weapon;
}