// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseEmpiresWeapon.h"
#include "BaseInfantryWeapon.generated.h"

/**
 * 
 */
UCLASS(HideCategories = (Transform, Animation, Mesh, Tick, Materials, Shape, Physics, Collision, Rendering, PhysicsVolume, Tags, Clothing, Lighting, Activation, Replication, Input, SkeletalMesh, Actor, Optimization))

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
