// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "EmpBaseWeapon.h"
#include "InstantFireType.h"


UInstantFireType::UInstantFireType()
	:Super()
{

}

void UInstantFireType::EmitShot(FVector Origin, FRotator Direction)
{
	//Do a trace and notify the weapon we have a hit

	const FVector EndPosition = Origin + (Direction.Vector() * MaximumTraceDistance);

	FCollisionQueryParams TraceParams(FName(TEXT("InstantWeaponTrace")), true);
	TraceParams.bTraceAsyncScene = true;
	

	FHitResult Hit;

	if (GetWorld()->LineTraceSingle(Hit, Origin, EndPosition, COLLISION_PROJECTILE, TraceParams))
	{
		GetWeapon()->OnBulletHit(Hit);
	}

	
	
}


