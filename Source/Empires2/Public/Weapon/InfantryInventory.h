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
		Slot_Skill4 = 7,
		Slot_None = 8,
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


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = General)
	TArray<TSubclassOf<ABaseInfantryWeapon>> Weapons;
	
	TArray<ABaseInfantryWeapon*> ConstructedWeapons;

	//TODO: Abilities, Skills, etc
	
};
