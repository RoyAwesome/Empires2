// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseEmpiresWeapon.h"
#include "BaseInfantryWeapon.generated.h"

/**
 * 
 */
UCLASS()
class EMPIRES2_API ABaseInfantryWeapon : public ABaseEmpiresWeapon
{
	GENERATED_BODY()

public:

	ABaseInfantryWeapon(const class FObjectInitializer & ObjectInitializer);

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display)
	class UAnimMontage* DrawWeaponAnimation;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display)
	class UAnimMontage* PutAwayWeaponAnimation;

	virtual void Equip() override;

};
