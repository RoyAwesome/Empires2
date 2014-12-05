// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon/Firetypes/WeaponFireType.h"
#include "InstantFireType.generated.h"

/**
 * 
 */
UCLASS()
class EMPIRES2_API UInstantFireType : public UWeaponFireType
{
	GENERATED_BODY()

public:

	UInstantFireType();

	virtual void EmitShot(FVector Origin, FRotator Direction) override;
	
	UPROPERTY(EditAnywhere, Category=General)
	float MaximumTraceDistance;

};
