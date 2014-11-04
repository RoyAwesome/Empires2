// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseFiremode.h"
#include "SingleShotFiremode.generated.h"

/**
 * 
 */
UCLASS()
class EMPIRES2_API USingleShotFiremode : public UBaseFiremode
{
	GENERATED_UCLASS_BODY()

		//FIRE CONTROL
public:

	virtual void BeginFire() override;

	virtual void EndFire() override;

	virtual void HandleFire() override;
	
};
