// Copyright 2015 Infinite Machine Studios.

#pragma once

#include "Object.h"
#include "EmpLevelInfo.generated.h"

/**
 *
 */
UCLASS(NotPlaceable)
class EMPIRES2_API UEmpLevelInfo : public UObject
{
	GENERATED_BODY()
public:


	UEmpLevelInfo(const FObjectInitializer& ObjectInit)
		: Super(ObjectInit)
	{
		OptimalPlayers = 32;
		Author = TEXT("Unknown");
		Description = NSLOCTEXT("LevelInfo", "DefaultDesc", "Needs Description");

	}

	UPROPERTY(EditInstanceOnly, BlueprintReadonly, Category = LevelInfo)
	int32 OptimalPlayers;

	UPROPERTY(EditInstanceOnly, BlueprintReadonly, Category = LevelInfo)
	FString Author;

	UPROPERTY(EditInstanceOnly, BlueprintReadonly, Category = LevelInfo)
	FText Description;

	UPROPERTY(EditInstanceOnly, BlueprintReadonly, Category = LevelInfo)
	TArray<UTexture2D*> LoadingScreenImages;

	UPROPERTY(EditInstanceOnly, BlueprintReadonly,  Category = LevelInfo)
	UTexture2D* Minimap;


};
