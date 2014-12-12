// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Usable.generated.h"
/**
 * 
 */
UINTERFACE(MinimalAPI)
class UUsable : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class IUsable
{
	GENERATED_IINTERFACE_BODY()
	
public:

	virtual void OnUsed(AController* user);

	virtual void StopUsed(AController* user);

	virtual void DisplayPrompt(AController* User);

	virtual void HidePropmt();

	

	UFUNCTION(BlueprintImplementableEvent, Category="Usable", meta = (FriendlyName = "On Used"))
	void BTOnUsed(AController* User);

	UFUNCTION(BlueprintImplementableEvent, Category = "Usable",  meta = (FriendlyName = "Stop Used"))
	void BTStopUsed(AController* User);

	UFUNCTION(BlueprintImplementableEvent, Category = "Usable", meta = (FriendlyName = "Display Prompt"))
	void BTDisplayPrompt(AController* User);

	UFUNCTION(BlueprintImplementableEvent, Category = "Usable", meta = (FriendlyName = "Hide Prompt"))
	void BTHidePrompt();

};
