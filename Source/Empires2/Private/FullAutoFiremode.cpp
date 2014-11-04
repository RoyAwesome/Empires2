// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BaseEmpiresWeapon.h"
#include "FullAutoFiremode.h"


UFullAutoFiremode::UFullAutoFiremode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


void UFullAutoFiremode::BeginFire()
{
	Super::BeginFire();

	//Start a timer based off the first shot time
	float FirstShotTime = Weapon->GetActiveFiremodeData().FirstShotFireDelay;
	if (FirstShotTime != 0)
	{
		GetWorld()->GetTimerManager().SetTimer(this, &UFullAutoFiremode::HandleFire, FirstShotTime, false);
	}
	else
	{
		HandleFire();
	}
}

void UFullAutoFiremode::HandleFire() 
{
	Weapon->FireShot();

	if (IsFiring())
	{
		//get the time until the next shot
		float FireTime = (1.0f / Weapon->GetActiveFiremodeData().RoundsPerMinute) * 60.0f;

		GetWorld()->GetTimerManager().SetTimer(this, &UFullAutoFiremode::HandleFire, FireTime, false);
	}
	else
	{
		SCREENLOG(TEXT("Stopped Firing"));
	}
}