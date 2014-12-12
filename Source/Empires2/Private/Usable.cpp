// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "Usable.h"

UUsable::UUsable(const class FObjectInitializer & ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Empty Constructor
}

void IUsable::OnUsed(AController* user)
{
	BTOnUsed(user);
}

void IUsable::StopUsed(AController* user)
{
	BTStopUsed(user);
}

void IUsable::DisplayPrompt(AController* User)
{
	BTDisplayPrompt(User);
}

void IUsable::HidePropmt()
{
	BTHidePrompt();
}
