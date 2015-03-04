// Copyright 2015 Infinite Machine Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeneralBlueprintFunctions.generated.h"

/**
 * 
 */
UCLASS()
class EMPIRES2_API UGeneralBlueprintFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public: 

	UFUNCTION(BlueprintPure, Category = "Object")
	static UObject* GetDefaultObjectFor(UClass* Clazz);
	
	
};
