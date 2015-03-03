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
	BPOnUsed(user);
}

void IUsable::StopUsed(AController* user)
{
	BPStopUsed(user);
}

void IUsable::DisplayPrompt(AController* User)
{
	BPDisplayPrompt(User);
}

void IUsable::HidePropmt()
{
	BPHidePrompt();
}
