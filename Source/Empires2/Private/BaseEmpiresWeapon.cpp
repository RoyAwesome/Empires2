// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "Empires2Character.h"
#include "BaseEmpiresProjectile.h"
#include "BaseEmpiresWeapon.h"


UBaseEmpiresWeapon::UBaseEmpiresWeapon(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
	GunOffset = FVector(100.0f, 30.0f, 10.0f);


}

void UBaseEmpiresWeapon::PostInitProperties()
{
	//Construct the firemodes

	Super::PostInitProperties();

}


void UBaseEmpiresWeapon::OnFire()
{
	
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = OwningCharacter->GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = OwningCharacter->GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = OwningCharacter->GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			ABaseEmpiresProjectile* projectile = World->SpawnActor<ABaseEmpiresProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			projectile->OwningWeapon = this;

			//And look at it go!
		}
		else
		{
			SCREENLOG(TEXT("Cannot fire weapon, World is Null"));
		}
	}
	else
	{
		SCREENLOG(TEXT("Cannot fire weapon, Projectile is Null"));
	}

	
}

void UBaseEmpiresWeapon::SetOwner(class AEmpires2Character* Owner)
{
	OwningCharacter = Owner;	
}