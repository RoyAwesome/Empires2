// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Core.h"
#include "BaseEmpiresInventory.generated.h"

UENUM(BlueprintType)
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
		Slot_Count = 8,
		Slot_None = 9,
	};
}


/**
 * 
 */
UCLASS()
class EMPIRES2_API UBaseEmpiresInventory : public UActorComponent
{
	GENERATED_BODY()
public:

	UBaseEmpiresInventory(const class FObjectInitializer & ObjectInitializer);
	

	///HACKHACK: These are individual pointers because an array of pointers does not replicate correctly


	UPROPERTY(VisibleAnywhere, Category = General, ReplicatedUsing=OnRep_Pistol)
	class ABaseEmpiresWeapon* Pistol;
	UPROPERTY(VisibleAnywhere, Category = General, ReplicatedUsing = OnRep_Primary)
	ABaseEmpiresWeapon* Primary;
	UPROPERTY(VisibleAnywhere, Category = General, ReplicatedUsing = OnRep_Tertiary)
	ABaseEmpiresWeapon* Tertiary;
	UPROPERTY(VisibleAnywhere, Category = General, ReplicatedUsing = OnRep_Special)
	ABaseEmpiresWeapon* Special;

	UFUNCTION()
	void OnRep_Pistol();
	UFUNCTION()
	void OnRep_Primary();
	UFUNCTION()
	void OnRep_Tertiary();
	UFUNCTION()
	void OnRep_Special();
		
	void OnRep_Any();

	virtual void ClearInventory();

	virtual void AddItem(EInfantryInventorySlots::Type Slot, ABaseEmpiresWeapon* Item);

	virtual ABaseEmpiresWeapon* GetItemInSlot(EInfantryInventorySlots::Type Slot);

	virtual int32 GetInventorySize()
	{
		return EInfantryInventorySlots::Slot_Count;
	}
	
};
