// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "InfantryClass.generated.h"


//Class slot filters
namespace EInfantryWeaponTypes
{
	enum Type
	{
		WeaponClass_Pistol = 0,
		WeaponClass_Rifle = 1,
		WeaponClass_SMG = 2,
		WeaponClass_Rocket = 3,
		WeaponClass_Siege = 4, //Mortars, other possible siege weapons

		WeaponClass_Grenade = 5,
		WeaponClass_Tool = 6,
		WeaponClass_Deployable = 7,
	};

}

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

};
