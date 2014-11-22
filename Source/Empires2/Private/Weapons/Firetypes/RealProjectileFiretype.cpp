// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BaseEmpiresProjectile.h"
#include "RealProjectileFiretype.h"


URealProjectileFiretype::URealProjectileFiretype(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bIsTicked = false;
}

void URealProjectileFiretype::EmitShot(FVector Origin, FRotator Direction)
{
	UWorld* World = GetWorld();
	if (World != NULL)
	{
		// spawn the projectile at the muzzle
		ABaseEmpiresProjectile* projectile = World->SpawnActor<ABaseEmpiresProjectile>(RealProjectileClass, Origin, Direction);
		projectile->OwningWeapon = GetWeapon();

		//And look at it go!
	}
}


