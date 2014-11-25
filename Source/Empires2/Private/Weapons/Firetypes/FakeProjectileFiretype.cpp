// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BaseEmpiresWeapon.h"
#include "FakeProjectileFiretype.h"

const FVector Gravity = FVector(0, 0, -981);

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
	Projectile.Velocity = Direction.Vector() * ProjectileSpeed;
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
	for (int32 i = ProjectilesToSim.Num(); i > 0; i--)
	{
		if (!ProjectilesToSim[i].bSimulating)
		{
			ProjectilesToSim.RemoveAt(i);
		}
	}
}

void UFakeProjectileFiretype::SimulateShot(FFakeProjectile& Projectile, float time)
{
	FVector EndPos = Projectile.CurrentPosition + Projectile.Velocity + Gravity * GravityScale;


	FCollisionQueryParams TraceParams(FName(TEXT("FakeProjectileTrace")), true);
	TraceParams.bTraceAsyncScene = true;

	FHitResult Hit;

	GetWorld()->LineTraceSingle(Hit, Projectile.CurrentPosition, EndPos, COLLISION_PROJECTILE, TraceParams);

	AEmpires2Character* Character = Cast<AEmpires2Character>(Hit.GetActor());
	if (Character)
	{
		GetWeapon()->DealDamage(Character);
		Projectile.bSimulating = false;
	}

	Projectile.CurrentPosition = EndPos;
	Projectile.Velocity += (Gravity * GravityScale);


}


