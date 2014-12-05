// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BaseInfantryWeapon.h"


ABaseInfantryWeapon::ABaseInfantryWeapon(const class FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAlwaysRelevant = true;
}

void ABaseInfantryWeapon::Equip()
{
	Super::Equip();

	PlayAnimation(DrawWeaponAnimation);
}
