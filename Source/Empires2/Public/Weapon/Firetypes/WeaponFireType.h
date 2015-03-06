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
	GENERATED_BODY()

public:
	UWeaponFireType();


	bool bIsTicked;


	virtual void Tick(float deltaTime);

	virtual void EmitShot(FVector Origin, FRotator Direction);

	virtual class UWorld* GetWorld() const override;
	virtual class AEmpBaseWeapon* GetWeapon() const;
};
