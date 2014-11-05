// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseEmpiresWeapon.h"
#include "BaseInfantryWeapon.generated.h"

/**
 * 
 */
UCLASS()
class EMPIRES2_API UBaseInfantryWeapon : public UBaseEmpiresWeapon
{
	GENERATED_UCLASS_BODY()

public:
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display)
	class UAnimMontage* DrawWeaponAnimation;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display)
	class UAnimMontage* PutAwayWeaponAnimation;

	virtual void Equip() override;

};
