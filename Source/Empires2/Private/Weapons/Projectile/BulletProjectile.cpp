// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Empires2.h"
#include "BulletProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABulletProjectile::ABulletProjectile(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PhysicsHitScale = 0.5f;

	
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ABulletProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Add some impulse to physics objects
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation((GetVelocity() * 100.0f) * PhysicsHitScale, GetActorLocation());
				
	}

	Super::OnHit(OtherActor, OtherComp, NormalImpulse, Hit);
	
}