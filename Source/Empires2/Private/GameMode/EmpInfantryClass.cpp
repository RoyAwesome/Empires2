// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "EmpInfantryClass.h"



UEmpInfantryClass::UEmpInfantryClass(const class FObjectInitializer & ObjectInitializer)
	:Super(ObjectInitializer)
{
	DefaultPistol = 0;
	DefaultPrimary = 0;
	DefaultTertiary = 0;
	DefaultActiveAbility = 0;

	NumPassives = 4;

	bIsOnGUI = true;
}

FEmpClassLoadout UEmpInfantryClass::GetDefaultLoadout()
{
	return FEmpClassLoadout(this);
}

FEmpClassLoadout::FEmpClassLoadout(UEmpInfantryClass* LoadoutClass)
	: LoadoutClass(LoadoutClass)
	, SelectedPistol(LoadoutClass->DefaultPistol)
	, SelectedPrimary(LoadoutClass->DefaultPrimary)
	, SelectedTertiary(LoadoutClass->DefaultTertiary)
	, SelectedActive(LoadoutClass->DefaultActiveAbility)
{
	SelectedPassives.AddUninitialized(LoadoutClass->NumPassives);
	LoadoutName = FText::Format(NSLOCTEXT("Loadout", "Loadout Format", "Custom {0} Loadout"), LoadoutClass->UIName);
}

