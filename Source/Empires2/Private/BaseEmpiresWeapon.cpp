// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "Empires2Character.h"
#include "BaseEmpiresProjectile.h"
#include "BaseFiremode.h"
#include "BaseEmpiresWeapon.h"


UBaseEmpiresWeapon::UBaseEmpiresWeapon(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
	GunOffset = FVector(100.0f, 30.0f, 10.0f);
	ActiveFiremode = 0;

}

void UBaseEmpiresWeapon::PostInitProperties()
{
	Super::PostInitProperties();

	//Construct the firemodes
	for (int32 i = 0; i < FiremodeClasses.Num(); i++)
	{
		if (FiremodeClasses[i] == nullptr)
		{
			SCREENLOG(TEXT("[%s] Error constructing firemode %d, Firemode is null"), GetName(), i);
			continue;
		}
		UBaseFiremode* firemode = ConstructObject<UBaseFiremode>(FiremodeClasses[i]);
		
		firemode->SetWeapon(this);
		Firemodes.Add(firemode);
	}
}

UWorld* UBaseEmpiresWeapon::GetWorld() const
{
	check(OwningCharacter);
	return OwningCharacter->GetWorld();
}


bool UBaseEmpiresWeapon::CanFire()
{
	UBaseFiremode* firemode = GetActiveFiremode();
	if (firemode == nullptr) return false; //No active firemode
	//TODO: Check if the firemode is capable of firing
	
	return true;
}

void UBaseEmpiresWeapon::BeginFire()
{
	UBaseFiremode* firemode = GetActiveFiremode();
	check(firemode);
	firemode->BeginFire();

}

void UBaseEmpiresWeapon::EndFire()
{
	UBaseFiremode* firemode = GetActiveFiremode();
	check(firemode);
	firemode->EndFire();
}


void UBaseEmpiresWeapon::FireShot()
{
	check(OwningCharacter);

	//Get the current firemode's projectile
	FAmmoPool ammoPool = GetCurrentAmmoPool();
	
	if (ammoPool.ProjectileClass == nullptr)
	{
		SCREENLOG(TEXT("Unable to fire Weapon %s, firemode %d because projectile is null!"), GetName(), ActiveFiremode);
		return;
	}

	const FRotator SpawnRotation = OwningCharacter->GetControlRotation();
	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	const FVector SpawnLocation = OwningCharacter->GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		// spawn the projectile at the muzzle
		ABaseEmpiresProjectile* projectile = World->SpawnActor<ABaseEmpiresProjectile>(ammoPool.ProjectileClass, SpawnLocation, SpawnRotation);
		projectile->OwningWeapon = this;

		//And look at it go!
	}

	// try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(OwningCharacter, FireSound, OwningCharacter->GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{

		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = OwningCharacter->Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UBaseEmpiresWeapon::SetOwner(class AEmpires2Character* Owner)
{
	OwningCharacter = Owner;	
}