// Copyright 2015 Infinite Machine Studios.

#include "Empires2.h"
#include "EmpBaseWorldSettings.h"
#include "EmpLevelInfo.h"





AEmpBaseWorldSettings::AEmpBaseWorldSettings(const FObjectInitializer& ObjectInit)
	: Super(ObjectInit)
{

}

void AEmpBaseWorldSettings::PostInitProperties()
{
	Super::PostInitProperties();
	CreateLevelInfo();
}

void AEmpBaseWorldSettings::PostLoad()
{
	Super::PostLoad();
	if (!HasAnyFlags(RF_NeedLoad))
	{
		CreateLevelInfo();
	}
}

void AEmpBaseWorldSettings::CreateLevelInfo()
{
	if (!IsTemplate())
	{
		//Need the name to be reliable so we can get the level info without loading the whole map
		static FName NAME_LevelInfo(TEXT("LevelInfo"));
		if (LevelInfo == nullptr)
		{
			LevelInfo = FindObject<UEmpLevelInfo>(UEmpLevelInfo::StaticClass(), *NAME_LevelInfo.ToString());
			if (LevelInfo == nullptr)
			{
				LevelInfo = ConstructObject<UEmpLevelInfo>(UEmpLevelInfo::StaticClass(), GetOutermost(), NAME_LevelInfo, RF_Standalone);
			}
		}
		else if (LevelInfo->GetFName() != NAME_LevelInfo)
		{
			// Duplicate the object because it's not safe to rename the object in PostLoad
			LevelInfo = DuplicateObject<UEmpLevelInfo>(LevelInfo, GetOutermost(), *NAME_LevelInfo.ToString());
		}
		
	}
}

AEmpBaseWorldSettings* AEmpBaseWorldSettings::GetWorldSettings(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr) return nullptr;
	if (WorldContextObject->GetWorld() == nullptr) return nullptr;
	return Cast<AEmpBaseWorldSettings>(WorldContextObject->GetWorld()->GetWorldSettings());
}
