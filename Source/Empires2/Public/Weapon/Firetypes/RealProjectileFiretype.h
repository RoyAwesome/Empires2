// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponFireType.h"
#include "Components/ActorComponent.h"
#include "RealProjectileFiretype.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class EMPIRES2_API URealProjectileFiretype : public UWeaponFireType
{
	GENERATED_UCLASS_BODY()
public:

		
		UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABaseEmpiresProjectile> RealProjectileClass;
	

		virtual void EmitShot(FVector Origin, FRotator Direction) override;


};
