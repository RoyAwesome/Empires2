// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "EmpBaseInfantryWeapon.h"


AEmpBaseInfantryWeapon::AEmpBaseInfantryWeapon(const class FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAlwaysRelevant = true;
}

void AEmpBaseInfantryWeapon::Equip()
{
	Super::Equip();

	PlayAnimation(DrawWeaponAnimation);
}
