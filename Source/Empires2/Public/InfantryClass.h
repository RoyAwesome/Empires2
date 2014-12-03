// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "InfantryClass.generated.h"


/**
 *
 */
UCLASS()
class EMPIRES2_API UInfantryClass : public UDataAsset
{
	GENERATED_UCLASS_BODY()

public:
	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SelectedLoadout)
		TSubclassOf<class ABaseInfantryWeapon> Pistol;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SelectedLoadout)
		TSubclassOf<ABaseInfantryWeapon> Primary;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SelectedLoadout)
	TSubclassOf<ABaseInfantryWeapon> Tertiary;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SelectedLoadout)
	TSubclassOf<class ABaseActiveAbility> ActiveAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SelectedLoadout)
	TSubclassOf<class ABasePassiveAbility> PassiveSlot1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SelectedLoadout)
	TSubclassOf<class ABasePassiveAbility> PassiveSlot2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SelectedLoadout)
	TSubclassOf<class ABasePassiveAbility> PassiveSlot3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SelectedLoadout)
	TSubclassOf<class ABasePassiveAbility> PassiveSlot4;


	/* List of all possible Pistols that can be selected */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PossibleItems)
		TArray<TSubclassOf<ABaseInfantryWeapon>> Pistols;
	/* List of all possible Primary Weapons that can be selected */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PossibleItems)
		TArray<TSubclassOf<ABaseInfantryWeapon>> Primaries;
	/* List of all grenades that can be selected */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PossibleItems)
		TArray<TSubclassOf<ABaseInfantryWeapon>> Tertiaries;
	/* List of all possible Active Abilities that can be used*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PossibleItems)
		TArray<TSubclassOf<ABaseActiveAbility>> ActiveAbilities;
	/* List of possible active abilities that this class can select  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PossibleItems)
		TArray<TSubclassOf<ABasePassiveAbility>> PassiveAbilities;

	/* Whether or not this class shows up on the UI as an option.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Config)
	bool bIsOnGUI;

	/* What order should this class be on the list. If multiple classes share the same value, then it sorts alphabetically */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Config)
	int32 SortOrder;
};
