// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BaseEmpiresWeapon.h"
#include "BurstFiremode.h"


UBurstFiremode::UBurstFiremode() 
	: Super()
{

}

void UBurstFiremode::BeginFire()
{
	Super::BeginFire();

	BurstsRemaining = ShotsInBurst;

	//Start a timer based off the first shot time
	float FirstShotTime = GetWeapon()->GetActiveFiremodeData().FirstShotFireDelay;
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
	if (!IsFiring()) return; //If we aren't firing anymore, don't fire a shot

	BurstsRemaining--;

	GetWeapon()->FireShot();
	
	if (BurstsRemaining > 0)
	{
		//get the time until the next shot
		float FireTime = (1.0f / GetWeapon()->GetActiveFiremodeData().RoundsPerMinute) * 60.0f;

		GetWorld()->GetTimerManager().SetTimer(this, &UBurstFiremode::HandleFire, FireTime, false);
	}
	
}

