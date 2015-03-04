// Copyright 2015 Infinite Machine Studios

#include "Empires2.h"
#include "GeneralBlueprintFunctions.h"





UObject* UGeneralBlueprintFunctions::GetDefaultObjectFor(UClass* Clazz)
{
	if (Clazz == nullptr) return nullptr;
	return GetMutableDefault<UObject>(Clazz);
}
