// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "EmpInfantryClass.generated.h"



/**
 *
 */
UCLASS(BlueprintType)
class EMPIRES2_API UEmpInfantryClass : public UDataAsset
{
	GENERATED_BODY()

public:
		
	UEmpInfantryClass(const class FObjectInitializer & ObjectInitializer);

	/* List of all possible Pistols that can be selected */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
		TArray<TSubclassOf<class AEmpBaseInfantryWeapon>> Pistols;
	/* List of all possible Primary Weapons that can be selected */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
		TArray<TSubclassOf<AEmpBaseInfantryWeapon>> Primaries;
	/* List of all grenades that can be selected */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
		TArray<TSubclassOf<AEmpBaseInfantryWeapon>> Tertiaries;
	/* List of all possible Active Abilities that can be used*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
		TArray<TSubclassOf<class ABaseActiveAbility>> ActiveAbilities;
	/* List of possible active abilities that this class can select  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
		TArray<TSubclassOf<class ABasePassiveAbility>> PassiveAbilities;

	/* Whether or not this class shows up on the UI as an option.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=GUI)
	bool bIsOnGUI;

	/* What order should this class be on the list. If multiple classes share the same value, then it sorts alphabetically */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GUI)
	int32 SortOrder;

	/* The name of this class on the UI */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GUI)
	FText UIName;

	/* The description of this class on the UI */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GUI)
	FText UIDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
	int32 DefaultPistol;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
	int32 DefaultPrimary;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
	int32 DefaultTertiary;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
	int32 DefaultActiveAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
	int32 NumPassives;


};


USTRUCT(BlueprintType)
struct FEmpClassLoadout
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Loadout")
	UEmpInfantryClass* LoadoutClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Loadout")
		int32 SelectedPistol;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Loadout")
		int32 SelectedPrimary;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Loadout")
		int32 SelectedTertiary;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Loadout")
		int32 SelectedActive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Loadout")
		TArray<int32> SelectedPassives;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Loadout")
		FText LoadoutName;


	FEmpClassLoadout()
		: SelectedPistol(-1)
		, SelectedPrimary(-1)
		, SelectedTertiary(-1)
		, SelectedActive(-1)
	{
		SelectedPassives.AddUninitialized(4);
		LoadoutName = FText::FromString(TEXT("Custom Loadout"));
	}

	FEmpClassLoadout(UEmpInfantryClass* LoadoutClass)
		: LoadoutClass(LoadoutClass)
		, SelectedPistol(LoadoutClass->DefaultPistol)
		, SelectedPrimary(LoadoutClass->DefaultPrimary)
		, SelectedTertiary(LoadoutClass->DefaultTertiary)
		, SelectedActive(LoadoutClass->DefaultActiveAbility)
	{
		SelectedPassives.AddUninitialized(LoadoutClass->NumPassives);
		LoadoutName = FText::Format(NSLOCTEXT("Loadout", "Loadout Format", "Custom {0} Loadout"), LoadoutClass->UIName);
	}

};
