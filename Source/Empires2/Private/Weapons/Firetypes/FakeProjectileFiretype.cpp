// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BaseEmpiresWeapon.h"
#include "FakeProjectileFiretype.h"

const FVector Gravity = FVector(0, 0, -981);

static TAutoConsoleVariable<int32> CVarDisplayFakeProjectileTraces(TEXT("emp.DesignDisplayFakeProjectiles"), 0,
	TEXT("empDesignDisplayFakeProjectiles [bool] - Displays fake projectile traces"));

UFakeProjectileFiretype::UFakeProjectileFiretype()
	:Super()
{
	bIsTicked = true;

	MaxTravelDistance = 100000; //1unit = 1cm.  This is 1km
}

void UFakeProjectileFiretype::EmitShot(FVector Origin, FRotator Direction)
{
	//Create a new shot
	FFakeProjectile Projectile;
	Projectile.Origin = Origin;
	Projectile.CurrentPosition = Origin;
	Projectile.Direction = Direction;
	Projectile.Velocity = Direction.Vector() * ProjectileSpeed;
	Projectile.bSimulating = true;

	ProjectilesToSim.Add(Projectile);
}

void UFakeProjectileFiretype::Tick(float deltaTime)
{

	for (int32 i = 0; i < ProjectilesToSim.Num(); i++)
	{
		FFakeProjectile& Projectile = ProjectilesToSim[i];
		if (Projectile.bSimulating) SimulateShot(Projectile, deltaTime);		
	}

	
	//TODO: Clean up the fake projectiles
	
}

void UFakeProjectileFiretype::SimulateShot(FFakeProjectile& Projectile, float time)
{

	FVector EndPos = Projectile.CurrentPosition + (Projectile.Velocity +  (.5f * Gravity * GravityScale * time)) * time;

	if (CVarDisplayFakeProjectileTraces.GetValueOnGameThread())
	{
		DrawDebugLine(GetWorld(), Projectile.CurrentPosition, EndPos, FColor::Green, true, -1.0f, 0, 1);
	}


	FCollisionQueryParams TraceParams(FName(TEXT("FakeProjectileTrace")), true);
	TraceParams.bTraceAsyncScene = true;

	FHitResult Hit;

	if (GetWorld()->LineTraceSingle(Hit, Projectile.CurrentPosition, EndPos, COLLISION_PROJECTILE, TraceParams))
	{
		//Inform the weapon that we hit a target
		GetWeapon()->OnBulletHit(Hit);

		//Stop simulating this bullet
		Projectile.bSimulating = false;
		if (CVarDisplayFakeProjectileTraces.GetValueOnGameThread())
		{
			DrawDebugSphere(GetWorld(), Hit.Location, 24, 32, FColor::Green, true);
		}
	}
	else
	{
		Projectile.CurrentPosition = EndPos;
		Projectile.Velocity += (Gravity * GravityScale) * time;
		float dist = FVector::Dist(Projectile.CurrentPosition, Projectile.Origin);
		if (dist >= MaxTravelDistance)
		{
			Projectile.bSimulating = false;
		}
	}
}


