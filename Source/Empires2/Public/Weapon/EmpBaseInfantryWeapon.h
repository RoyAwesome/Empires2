// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EmpBaseWeapon.h"
#include "EmpBaseInfantryWeapon.generated.h"

/**
 * 
 */
UCLASS()
class EMPIRES2_API AEmpBaseInfantryWeapon : public AEmpBaseWeapon
{
	GENERATED_BODY()

public:

	AEmpBaseInfantryWeapon(const class FObjectInitializer & ObjectInitializer);

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display)
	class UAnimMontage* DrawWeaponAnimation;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display)
	class UAnimMontage* PutAwayWeaponAnimation;

	virtual void Equip() override;

};
