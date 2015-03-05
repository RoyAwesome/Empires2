// Copyright 2015 Infinite Machine Studios.

#pragma once

#include "Engine/DataAsset.h"
#include "EmpTeam.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class EMPIRES2_API UEmpTeam : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category=UI)
	FText UIName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category=UI)
	FText UIDescription;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category=UI)
	UTexture2D* UITexture;

	//List of all classes that this team has access to
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category=Team)
	TArray<class UEmpInfantryClass*> Classes;

	//TODO: Array of Vehicles

	//TODO: Array of buildings	
	
};
