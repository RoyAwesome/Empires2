// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "SingleShotFiremode.h"


USingleShotFiremode::USingleShotFiremode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void USingleShotFiremode::BeginFire()
{
	Super::BeginFire();

	//Start a timer based off the first shot time
	float FirstShotTime = Weapon->GetActiveFiremodeData().FirstShotFireDelay;
	if (FirstShotTime != 0)
	{
		GetWorld()->GetTimerManager().SetTimer(this, &USingleShotFiremode::HandleFire, FirstShotTime, false);
	}
	else
	{
		HandleFire();
	}
	
}



void USingleShotFiremode::HandleFire()
{
	Weapon->FireShot();
}

