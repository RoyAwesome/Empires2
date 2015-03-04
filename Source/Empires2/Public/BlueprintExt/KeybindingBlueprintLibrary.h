// Copyright 2015 Infinite Machine Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "KeybindingBlueprintLibrary.generated.h"





USTRUCT(BlueprintType)
struct FDGInputMapping
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FName ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FString KeyAsString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		uint32 bShift : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		uint32 bCtrl : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		uint32 bAlt : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		uint32 bCmd : 1;


	FDGInputMapping(){}
	FDGInputMapping(const FName InActionName, const FKey InKey, const bool bInShift, const bool bInCtrl, const bool bInAlt, const bool bInCmd)
		: Key(InKey)
		, KeyAsString(Key.GetDisplayName().ToString())
		, bShift(bInShift)
		, bCtrl(bInCtrl)
		, bAlt(bInAlt)
		, bCmd(bInCmd)
	{
		ActionName = InActionName;
	}

	FDGInputMapping(const FInputActionKeyMapping& Action)
		: ActionName( Action.ActionName)
		, Key(Action.Key)
		, KeyAsString(Action.Key.GetDisplayName().ToString())
		, bShift(Action.bShift)
		, bCtrl(Action.bCtrl)
		, bAlt(Action.bAlt)
		, bCmd(Action.bCmd)
	{

	}
};

/**
 *
 */
UCLASS()
class EMPIRES2_API UKeybindingBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Input")
		static FKey GetKey(FName Text);

	UFUNCTION(BlueprintPure, Category = "Input")
	static FDGInputMapping GetKeybindForEvent(const FKeyEvent& KeyEvent);	

	UFUNCTION(BlueprintPure, Category = "Input")
		static void GetAllKeyBindings(TArray<FDGInputMapping>& Bindings);

	UFUNCTION(BlueprintCallable, Category = "Input")
		static bool RebindKey(FDGInputMapping Action);

};
