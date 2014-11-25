// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponFireType.h"
#include "Components/ActorComponent.h"
#include "FakeProjectileFiretype.generated.h"

USTRUCT()
struct FFakeProjectile
{
	GENERATED_USTRUCT_BODY()

public:

	/* Current position of this shot */
	UPROPERTY(VisibleAnywhere, Category=General)
	FVector CurrentPosition;
	/* The starting point of this shot */
	UPROPERTY(VisibleAnywhere, Category = General)
	FVector Origin;

	/* The direction this shot is traveling.  */
	UPROPERTY(VisibleAnywhere, Category=General)
	FRotator Direction;

	UPROPERTY(VisibleAnywhere, Category = General)
	FVector Velocity;

	/*True if this fake projectile should be updated.  False if it's queued for removal*/
	UPROPERTY(VisibleAnywhere, Category=General)
	bool bSimulating;

};

/**
 * Fake Projectile Simulation 
 */
UCLASS(Blueprintable, Abstract)
class EMPIRES2_API UFakeProjectileFiretype : public UWeaponFireType
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category=General)
		float ProjectileSpeed;
	UPROPERTY(EditDefaultsOnly, Category = General)
		float GravityScale;
		
	UPROPERTY(VisibleAnywhere, Category=General)
	TArray<FFakeProjectile> ProjectilesToSim;

	virtual void EmitShot(FVector Origin, FRotator Direction) override;

	virtual void Tick(float deltaTime) override;

	protected:
		virtual void SimulateShot(FFakeProjectile& Projectile, float time);

};
