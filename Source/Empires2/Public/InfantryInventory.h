// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BaseInfantryWeapon.h"
#include "InfantryInventory.generated.h"

namespace EInfantryInventorySlots
{
	enum Type
	{
		Slot_Sidearm = 0,
		Slot_Primary = 1,
		Slot_Tertiary = 2,
		Slot_Ability = 3,
		Slot_Skill1 = 4,
		Slot_Skill2 = 5,
		Slot_Skill3 = 6,
		Slot_Skill4 = 7
	};
}

/**
* Inventory for weapons
*/
USTRUCT()
struct EMPIRES2_API FInfantryInventory
{
	GENERATED_USTRUCT_BODY()

public:
	/*
	FInfantryInventory()
	{
	//Add two guns in here	
		static ConstructorHelpers::FClassFinder<UBaseInfantryWeapon> RifleClassFinder(TEXT("/Game/Blueprints/BE_Rifle"));
		Weapons.Insert(RifleClassFinder.Class, EInfantryInventorySlots::Slot_Primary);
		
		static ConstructorHelpers::FClassFinder<UBaseInfantryWeapon> PistolClassFinder(TEXT("/Game/Blueprints/BE_Pistol"));
		Weapons.Insert(PistolClassFinder.Class, EInfantryInventorySlots::Slot_Sidearm);
	}*/
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = General)
	TArray<TSubclassOf<UBaseInfantryWeapon>> Weapons;
	
	TArray<UBaseInfantryWeapon*> ConstructedWeapons;

	//TODO: Abilities, Skills, etc
	
};
