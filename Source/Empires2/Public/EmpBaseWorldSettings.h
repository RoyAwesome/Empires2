// Copyright 2015 Infinite Machine Studios.

#pragma once

#include "GameFramework/WorldSettings.h"
#include "EmpBaseWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class EMPIRES2_API AEmpBaseWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
public:
	AEmpBaseWorldSettings(const FObjectInitializer& ObjectInit);

	virtual void PostInitProperties() override;

	virtual void PostLoad() override;
	
	UFUNCTION(BlueprintCallable, Category = World)
	static AEmpBaseWorldSettings* GetWorldSettings(UObject* WorldContextObject);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = LevelInfo)
	class UEmpLevelInfo* LevelInfo;
protected:

	

	virtual void CreateLevelInfo();
	
};
