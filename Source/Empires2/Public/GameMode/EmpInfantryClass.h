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
		TArray<TSubclassOf<class ABaseInfantryWeapon>> Pistols;
	/* List of all possible Primary Weapons that can be selected */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
		TArray<TSubclassOf<ABaseInfantryWeapon>> Primaries;
	/* List of all grenades that can be selected */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
		TArray<TSubclassOf<ABaseInfantryWeapon>> Tertiaries;
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
