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

	//TODO: Class Item Filtering

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = General)
	TSubclassOf<class ABaseInfantryWeapon> Pistol;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = General)
		TSubclassOf<ABaseInfantryWeapon> Primary;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = General)
	TArray<TSubclassOf<ABaseInfantryWeapon>> Pistols;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = General)
	TArray<TSubclassOf<ABaseInfantryWeapon>> Primaries;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = General)
	TArray<TSubclassOf<ABaseInfantryWeapon>> Tertiaries;

	//TArray<TSubclassOf<UInfantryActiveAbility>> Actives;
	//TArray<TSubclassOf<UInfantryPassiveAbility>> Passives;
};
