// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Core.h"
#include "BaseEmpiresInventory.generated.h"


namespace EInfantryInventorySlots
{
	enum Type
	{
		Slot_None = -1,
		Slot_Sidearm = 0,
		Slot_Primary = 1,
		Slot_Tertiary = 2,
		Slot_Ability = 3,
		Slot_Skill1 = 4,
		Slot_Skill2 = 5,
		Slot_Skill3 = 6,
		Slot_Skill4 = 7,
		Slot_Count = 8,
	};
}


/**
 * 
 */
UCLASS()
class EMPIRES2_API UBaseEmpiresInventory : public UObject
{
	GENERATED_UCLASS_BODY()
public:

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}


	//TODO: Create an BaseEmpiresAbility actor so that everything you have in this array is abilities, including weapons
	UPROPERTY(Replicated)
	TArray<class ABaseEmpiresWeapon*> InventoryItems;

	virtual void ClearInventory();

	virtual void AddItem(EInfantryInventorySlots::Type Slot, ABaseEmpiresWeapon* Item);

	virtual ABaseEmpiresWeapon* GetItemInSlot(EInfantryInventorySlots::Type Slot);

	virtual int32 GetInventorySize()
	{
		return InventoryItems.Num();
	}
	
};
