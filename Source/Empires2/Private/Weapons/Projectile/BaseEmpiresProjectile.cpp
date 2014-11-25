// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BaseEmpiresProjectile.h"
#include "BaseEmpiresWeapon.h"
#include "GameFramework/ProjectileMovementComponent.h"



ABaseEmpiresProjectile::ABaseEmpiresProjectile(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	CollisionComp = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));

	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");			// Collision profiles are defined in DefaultEngine.ini
	CollisionComp->OnComponentHit.AddDynamic(this, &ABaseEmpiresProjectile::OnHit);		// set up a notification for when this component hits something blocking
	RootComponent = CollisionComp;

	
	ProjectileMovement = PCIP.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}


void ABaseEmpiresProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	check(OwningWeapon);
	if (OwningWeapon->OwningCharacter == nullptr) return;

	//TODO: Apply Damage
	if (OtherActor && OtherActor->bCanBeDamaged)
	{
		AEmpires2Character* Character = Cast<AEmpires2Character>(OtherActor);
		if (Character) OwningWeapon->DealDamage(Character);
	}

	Destroy();
}

