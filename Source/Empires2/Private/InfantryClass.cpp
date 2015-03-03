// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "InfantryClass.h"



UInfantryClass::UInfantryClass(const class FObjectInitializer & ObjectInitializer)
	:Super(ObjectInitializer)
{
	DefaultPistol = 0;
	DefaultPrimary = 0;
	DefaultTertiary = 0;
	DefaultActiveAbility = 0;

	NumPassives = 4;

	bIsOnGUI = true;
}
