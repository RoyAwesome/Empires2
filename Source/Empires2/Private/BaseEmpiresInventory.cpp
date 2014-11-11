// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BaseEmpiresInventory.h"
#include "UnrealNetwork.h"




UBaseEmpiresInventory::UBaseEmpiresInventory(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	InventoryItems.AddZeroed(EInfantryInventorySlots::Slot_Count);
}


void UBaseEmpiresInventory::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseEmpiresInventory, InventoryItems);
}

void UBaseEmpiresInventory::ClearInventory()
{
	//I don't think I need to destroy everything here, but I may

	InventoryItems.Reset(EInfantryInventorySlots::Slot_Count);
}

void UBaseEmpiresInventory::AddItem(EInfantryInventorySlots::Type Slot, ABaseEmpiresWeapon* Item)
{
	InventoryItems.Insert(Item, Slot);
}

ABaseEmpiresWeapon* UBaseEmpiresInventory::GetItemInSlot(EInfantryInventorySlots::Type Slot)
{
	if (Slot >= InventoryItems.Num() || Slot == EInfantryInventorySlots::Slot_None) return nullptr;
	return InventoryItems[Slot];
}