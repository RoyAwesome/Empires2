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

//////////////////////GENERAL

void UBaseEmpiresWeapon::PostInitProperties()
{
	Super::PostInitProperties();

	//Construct the firemodes
	for (int32 i = 0; i < FiremodeData.Num(); i++)
	{
		if (FiremodeData[i].FiremodeClass == nullptr)
		{
			SCREENLOG(TEXT("[%s] Error constructing firemode %d, Firemode is null"), GetName(), i);
			continue;
		}
		UBaseFiremode* firemode = ConstructObject<UBaseFiremode>(FiremodeData[i].FiremodeClass);

		firemode->SetWeapon(this);
		Firemodes.Add(firemode);
	}
}

UWorld* UBaseEmpiresWeapon::GetWorld() const
{
	check(OwningCharacter);
	return OwningCharacter->GetWorld();
}

void UBaseEmpiresWeapon::SetOwner(class AEmpires2Character* Owner)
{
	OwningCharacter = Owner;
}

void UBaseEmpiresWeapon::PlaySound(USoundBase* Sound)
{
	// try and play the sound if specified
	if (Sound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(OwningCharacter, Sound, OwningCharacter->GetActorLocation());
	}
}

void UBaseEmpiresWeapon::PlayAnimation(UAnimMontage* Animation)
{
	// try and play a animation
	if (Animation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = OwningCharacter->Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(Animation, 1.f);
		}
	}
}

/////////////////////FIRE CONTROL

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
		UE_LOG(EmpiresGameplay, Display, TEXT("Unable to fire Weapon %s, firemode %d because projectile is null!"), GetName(), ActiveFiremode);
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

	PlaySound(FireSound);

	PlayAnimation(FireAnimation);

}

///////////////////////////////////// FIREMODES

void UBaseEmpiresWeapon::NextFiremode()
{
	if (GetActiveFiremode()->IsFiring()) return; //Don't change modes if we are shooting
	if (Firemodes.Num() == 1) return; //Don't change firemode if we only have one firemode

	//Play the animation and sound for changing the firemode.
	PlaySound(ChangeFiremodeSound);
	PlayAnimation(ChangeFiremodeAnimation);

	ActiveFiremode++;
	if (ActiveFiremode >= Firemodes.Num())
	{
		ActiveFiremode = 0;
	}
}