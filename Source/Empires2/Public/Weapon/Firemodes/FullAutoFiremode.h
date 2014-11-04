// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseFiremode.h"
#include "FullAutoFiremode.generated.h"

/**
 * 
 */
UCLASS()
class EMPIRES2_API UFullAutoFiremode : public UBaseFiremode
{
	GENERATED_UCLASS_BODY()

public:

	virtual void BeginFire() override;

	virtual void HandleFire() override;

	
};
