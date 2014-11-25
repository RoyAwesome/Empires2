// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "BaseEmpiresWeapon.h"
#include "InstantFireType.h"


UInstantFireType::UInstantFireType(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void UInstantFireType::EmitShot(FVector Origin, FRotator Direction)
{
	//Do a trace and notify the weapon we have a hit

	const FVector EndPosition = Origin + (Direction.Vector() * MaximumTraceDistance);

	FCollisionQueryParams TraceParams(FName(TEXT("InstantWeaponTrace")), true);
	TraceParams.bTraceAsyncScene = true;
	

	FHitResult Hit;

	GetWorld()->LineTraceSingle(Hit, Origin, EndPosition, COLLISION_PROJECTILE, TraceParams);

	
	AEmpires2Character* Character = Cast<AEmpires2Character>(Hit.GetActor());
	if (Character)
	{
		GetWeapon()->DealDamage(Character);
	}

}


