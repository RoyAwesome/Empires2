// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BaseEmpiresWeapon.h"
#include "WeaponFireType.h"


UWeaponFireType::UWeaponFireType(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bIsTicked = false;
}

class UWorld* UWeaponFireType::GetWorld() const
{
	ABaseEmpiresWeapon* Weap = Cast<ABaseEmpiresWeapon>(GetOuter());
	if (Weap) return Weap->GetWorld();
	else return nullptr;
}

void UWeaponFireType::Tick(float deltaTime)
{

}

void UWeaponFireType::EmitShot(FVector Origin, FRotator Direction)
{

}

class ABaseEmpiresWeapon* UWeaponFireType::GetWeapon() const
{
	return Cast<ABaseEmpiresWeapon>(GetOuter());
}


