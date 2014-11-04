// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BurstFiremode.h"


UBurstFiremode::UBurstFiremode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void UBurstFiremode::BeginFire()
{
	Super::BeginFire();

	BurstsRemaining = ShotsInBurst;

	//Start a timer based off the first shot time
	float FirstShotTime = Weapon->GetActiveFiremodeData().FirstShotFireDelay;
	if (FirstShotTime != 0)
	{
		GetWorld()->GetTimerManager().SetTimer(this, &UBurstFiremode::HandleFire, FirstShotTime, false);
	}
	else
	{
		HandleFire();
	}
}

void UBurstFiremode::HandleFire()
{
	BurstsRemaining--;

	Weapon->FireShot();
	
	if (IsFiring() && BurstsRemaining > 0)
	{
		//get the time until the next shot
		float FireTime = (1.0f / Weapon->GetActiveFiremodeData().RoundsPerMinute) * 60.0f;

		GetWorld()->GetTimerManager().SetTimer(this, &UBurstFiremode::HandleFire, FireTime, false);
	}
	
}

