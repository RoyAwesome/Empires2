// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "WeaponFireType.generated.h"

/**
 * 
 */
UCLASS(ABSTRACT)
class EMPIRES2_API UWeaponFireType : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	bool bIsTicked;


	virtual void Tick(float deltaTime);

	virtual void EmitShot(FVector Origin, FRotator Direction);

	virtual class UWorld* GetWorld() const override;
	virtual class ABaseEmpiresWeapon* GetWeapon() const;
};
