// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "EmpBaseWeapon.h"
#include "WeaponFireType.h"


UWeaponFireType::UWeaponFireType()
	: Super()
{
	bIsTicked = false;
}

class UWorld* UWeaponFireType::GetWorld() const
{
	AEmpBaseWeapon* Weap = Cast<AEmpBaseWeapon>(GetOuter());
	if (Weap) return Weap->GetWorld();
	else return nullptr;
}

void UWeaponFireType::Tick(float deltaTime)
{

}

void UWeaponFireType::EmitShot(FVector Origin, FRotator Direction)
{

}

class AEmpBaseWeapon* UWeaponFireType::GetWeapon() const
{
	return Cast<AEmpBaseWeapon>(GetOuter());
}


