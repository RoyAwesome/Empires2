// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "BaseEmpiresProjectile.h"
#include "BulletProjectile.generated.h"

UCLASS(config=Game)
class ABulletProjectile : public ABaseEmpiresProjectile
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Projectile)
	float PhysicsHitScale;

public:

	virtual void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

};

