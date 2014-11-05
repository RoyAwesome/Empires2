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





//////////////////////////EQUIPPING
void UBaseEmpiresWeapon::Equip()
{
	check(OwningCharacter);

	//Set the mesh to be the weapon we have
	OwningCharacter->Mesh1P->SetSkeletalMesh(ViewModel);
	OwningCharacter->Mesh1P->SetAnimation(GetActiveWeaponAnimationSet().FireAnimation);
}
void UBaseEmpiresWeapon::Unequip()
{

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
		//UE_LOG(EmpiresGameplay, Display, TEXT("Unable to fire Weapon %s, firemode %d because projectile is null!"), GetName(), ActiveFiremode);
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

	PlaySound(GetActiveWeaponAnimationSet().FireSound);
	PlayAnimation(GetActiveWeaponAnimationSet().FireAnimation);

	
	ConsumeAmmo(GetActiveFiremodeData().AmmoConsumedPerShot);

	//If we are out of ammo, stop firing and reload
	if (GetAmmoInClip() <= 0)
	{
		EndFire();
		//Reload();
	}

}

///////////////////////////////////// FIREMODES

void UBaseEmpiresWeapon::NextFiremode()
{
	if (GetActiveFiremode()->IsFiring()) return; //Don't change modes if we are shooting
	if (Firemodes.Num() == 1) return; //Don't change firemode if we only have one firemode

	//Play the animation and sound for changing the firemode.
	PlaySound(GetActiveWeaponAnimationSet().ChangeFiremodeSound);
	PlayAnimation(GetActiveWeaponAnimationSet().ChangeFiremodeAnimation);

	ActiveFiremode++;
	if (ActiveFiremode >= Firemodes.Num())
	{
		ActiveFiremode = 0;
	}
}

UBaseFiremode* UBaseEmpiresWeapon::GetFiremode(int32 Firemode)
{
	if (Firemode == CurrentFiremode)
	{
		return GetActiveFiremode();
	}
	else
	{
		check(Firemode >= 0 && Firemode < Firemodes.Num());
		return Firemodes[Firemode];
	}
}

FWeaponData UBaseEmpiresWeapon::GetFiremodeData(int32 Firemode)
{
	if (Firemode == CurrentFiremode)
	{
		return GetActiveFiremodeData();
	}
	else
	{
		check(Firemode >= 0 && Firemode < FiremodeData.Num());
		return FiremodeData[Firemode];
	}
}

////////////////////////////////// AMMO

FAmmoPool UBaseEmpiresWeapon::GetAmmoPool(int32 FromAmmoPool)
{
	if (FromAmmoPool == CurrentAmmopool)
	{
		return GetCurrentAmmoPool();
	}
	else
	{
		check(FromAmmoPool >= 0 && FromAmmoPool < AmmoPools.Num());
		return AmmoPools[FromAmmoPool];
	}
}

void UBaseEmpiresWeapon::ConsumeAmmo(int32 HowMuch, int32 FromAmmoPool)
{
	FAmmoPool AmmoPool = GetAmmoPool(FromAmmoPool);

	AmmoPool.AmmoInClip -= HowMuch;
	AmmoPool.CurrentAmmo -= HowMuch;
}

int32 UBaseEmpiresWeapon::GetAmmoInClip(int32 FromAmmoPool)
{
	FAmmoPool AmmoPool = GetAmmoPool(FromAmmoPool);
	return AmmoPool.AmmoInClip;
}

int32 UBaseEmpiresWeapon::GetTotalAmmo(int32 FromAmmoPool)
{
	FAmmoPool AmmoPool = GetAmmoPool(FromAmmoPool);
	return AmmoPool.CurrentAmmo;
}

void UBaseEmpiresWeapon::AddAmmo(int32 Ammount, int32 ToAmmoPool)
{
	FAmmoPool AmmoPool = GetAmmoPool(ToAmmoPool);
	AmmoPool.CurrentAmmo += Ammount;
	if (AmmoPool.CurrentAmmo > AmmoPool.MaxAmmo)
	{
		AmmoPool.CurrentAmmo = AmmoPool.MaxAmmo;
	}
}

void UBaseEmpiresWeapon::Reload(int32 AmmoPool)
{

}
