// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseFiremode.h"
#include "BurstFiremode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class EMPIRES2_API UBurstFiremode : public UBaseFiremode
{
	GENERATED_UCLASS_BODY()

public:
	virtual void BeginFire() override;

	virtual void HandleFire() override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Firemode)
	int32 ShotsInBurst;
protected:
	int32 BurstsRemaining;

	
};
