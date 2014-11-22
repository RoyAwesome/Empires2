// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "FakeProjectileFiretype.h"


UFakeProjectileFiretype::UFakeProjectileFiretype(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bIsTicked = true;
}

void UFakeProjectileFiretype::EmitShot(FVector Origin, FRotator Direction)
{
	//Create a new shot
	FFakeProjectile Projectile;
	Projectile.Origin = Origin;
	Projectile.Direction = Direction;
	Projectile.bSimulating = true;

	ProjectilesToSim.Add(Projectile);
}

void UFakeProjectileFiretype::Tick(float deltaTime)
{
	for (int32 i = 0; i < ProjectilesToSim.Num(); i++)
	{
		if(ProjectilesToSim[i].bSimulating) SimulateShot(ProjectilesToSim[i], deltaTime);
	}

	//Clean up the non-simulating projectiles
}

void UFakeProjectileFiretype::SimulateShot(FFakeProjectile& Projectile, float time)
{
	//TODO: Simulate the shot
}


