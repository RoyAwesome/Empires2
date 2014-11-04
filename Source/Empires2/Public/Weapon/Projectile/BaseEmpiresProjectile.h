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
	GENERATED_UCLASS_BODY()

public: 
	
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    TSubobjectPtr<class USphereComponent> CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	TSubobjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	class UBaseEmpiresWeapon* OwningWeapon;

	/** called when projectile hits something */
	UFUNCTION()
	virtual void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
};
