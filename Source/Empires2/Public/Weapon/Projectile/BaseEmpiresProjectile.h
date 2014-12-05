// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseEmpiresProjectile.generated.h"

/**
 * 
 */
UCLASS()
class EMPIRES2_API ABaseEmpiresProjectile : public AActor
{
	GENERATED_BODY()

public: 
	ABaseEmpiresProjectile(const class FObjectInitializer & ObjectInitializer);


	class ABaseEmpiresWeapon* OwningWeapon;

	/** called when projectile hits something */
	UFUNCTION()
	virtual void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	

private:
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UProjectileMovementComponent* ProjectileMovement;

public:

	USphereComponent* GetCollisionComponent() const
	{
		return CollisionComp;
	}

	UProjectileMovementComponent* GetProjectileMovement() const
	{
		return ProjectileMovement;
	}
	
};
