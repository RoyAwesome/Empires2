// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "Empires2Character.h"
#include "BaseEmpiresProjectile.h"
#include "BaseFiremode.h"
#include "BaseEmpiresWeapon.h"


ABaseEmpiresWeapon::ABaseEmpiresWeapon(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	GunOffset = FVector(100.0f, 30.0f, 10.0f);
	ActiveFiremode = 0;
	bReloading = false;
}

//////////////////////GENERAL

void ABaseEmpiresWeapon::PostInitProperties()
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

UWorld* ABaseEmpiresWeapon::GetWorld() const
{
	check(OwningCharacter);
	return OwningCharacter->GetWorld();
}

void ABaseEmpiresWeapon::SetOwner(class AEmpires2Character* Owner)
{
	OwningCharacter = Owner;
}

void ABaseEmpiresWeapon::PlaySound(USoundBase* Sound)
{
	// try and play the sound if specified
	if (Sound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(OwningCharacter, Sound, OwningCharacter->GetActorLocation());
	}
}

void ABaseEmpiresWeapon::PlayAnimation(UAnimMontage* Animation)
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
void ABaseEmpiresWeapon::Equip()
{
	check(OwningCharacter);

	//Set the mesh to be the weapon we have
	OwningCharacter->Mesh1P->SetSkeletalMesh(ViewModel);
	OwningCharacter->Mesh1P->SetAnimation(GetActiveWeaponAnimationSet().FireAnimation);
}
void ABaseEmpiresWeapon::Unequip()
{

}



/////////////////////FIRE CONTROL

bool ABaseEmpiresWeapon::CanFire()
{
	UBaseFiremode* firemode = GetActiveFiremode();
	if (firemode == nullptr) return false; //No active firemode
	if (bReloading) return false; //Can't fire when we are reloading
	if (GetCurrentAmmoPool().AmmoInClip <= 0) return false; //If we have no ammo, we can't fire
	
	//TODO: Check if the firemode is capable of firing


	return true;
}

void ABaseEmpiresWeapon::BeginFire()
{
	if (!CanFire()) return; //Don't Fire if we can't fire
	if (GetCurrentAmmoPool().AmmoInClip <= 0) //If we are out of ammo, attempt to reload
	{
		Reload();
		return;
	}

	UBaseFiremode* firemode = GetActiveFiremode();
	check(firemode);
	firemode->BeginFire();

	bIsFiring = true;
	ShotsFired = 0;

}

void ABaseEmpiresWeapon::EndFire()
{
	UBaseFiremode* firemode = GetActiveFiremode();
	check(firemode);
	firemode->EndFire();

	bIsFiring = false;
}


void ABaseEmpiresWeapon::FireShot()
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

	FVector AimDirection = GetFireDirection();

	DrawDebugLine(GetWorld(), SpawnLocation, SpawnLocation + (AimDirection * 1000), FColor::Blue, true, -1.0f, 0, 1);
	FVector CofDirection = AdjustByCof(AimDirection);
	DrawDebugLine(GetWorld(), SpawnLocation, SpawnLocation + (CofDirection * 1000), FColor::Red, true, -1.0f, 0, 1);

	FRotator ConeAdjustedAngle = CofDirection.Rotation();

	UWorld* const World = GetWorld();


	if (World != NULL)
	{
		// spawn the projectile at the muzzle
		ABaseEmpiresProjectile* projectile = World->SpawnActor<ABaseEmpiresProjectile>(ammoPool.ProjectileClass, SpawnLocation, ConeAdjustedAngle);
		projectile->OwningWeapon = this;

		//And look at it go!
	}

	PlaySound(GetActiveWeaponAnimationSet().FireSound);
	PlayAnimation(GetActiveWeaponAnimationSet().FireAnimation);

	
	ConsumeAmmo(GetActiveFiremodeData().AmmoConsumedPerShot);
	ShotsFired++;

	//Recoil the shot
	OwningCharacter->AddControllerPitchInput(-RollVerticalRecoil());
	OwningCharacter->AddControllerYawInput(RollHorizontalRecoil());


	//If we are out of ammo, stop firing and reload
	if (GetAmmoInClip() <= 0)
	{
		EndFire();
		Reload();
	}

}

FVector ABaseEmpiresWeapon::GetFireDirection()
{
	FVector Vec;
	FRotator Rot;
	OwningCharacter->GetController()->GetPlayerViewPoint(Vec, Rot);
	return Rot.Vector();
}

///////////////////////////////////// FIREMODES
FWeaponData ABaseEmpiresWeapon::GetActiveFiremodeData()
{

	return FiremodeData[ActiveFiremode];
}


UBaseFiremode* ABaseEmpiresWeapon::GetActiveFiremode()
{
	return Firemodes[ActiveFiremode];
}


FAmmoPool ABaseEmpiresWeapon::GetCurrentAmmoPool()
{
	return AmmoPools[FiremodeData[ActiveFiremode].AmmoPoolIndex];
}


void ABaseEmpiresWeapon::NextFiremode()
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

UBaseFiremode* ABaseEmpiresWeapon::GetFiremode(int32 Firemode)
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

FWeaponData ABaseEmpiresWeapon::GetFiremodeData(int32 Firemode)
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

FAmmoPool ABaseEmpiresWeapon::GetAmmoPool(int32 FromAmmoPool)
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

void ABaseEmpiresWeapon::ConsumeAmmo(int32 HowMuch, int32 FromAmmoPool)
{
	int32 AmmoPoolidx = FromAmmoPool == CurrentAmmopool ? GetActiveFiremodeData().AmmoPoolIndex : FromAmmoPool;

	AmmoPools[AmmoPoolidx].AmmoInClip -= HowMuch;
}

int32 ABaseEmpiresWeapon::GetAmmoInClip(int32 FromAmmoPool)
{
	FAmmoPool AmmoPool = GetAmmoPool(FromAmmoPool);
	return AmmoPool.AmmoInClip;
}

int32 ABaseEmpiresWeapon::GetTotalAmmo(int32 FromAmmoPool)
{
	FAmmoPool AmmoPool = GetAmmoPool(FromAmmoPool);
	return AmmoPool.CurrentAmmo;
}

void ABaseEmpiresWeapon::AddAmmo(int32 Ammount, int32 ToAmmoPool)
{
	FAmmoPool AmmoPool = GetAmmoPool(ToAmmoPool);
	AmmoPool.CurrentAmmo += Ammount;
	if (AmmoPool.CurrentAmmo > AmmoPool.MaxAmmo)
	{
		AmmoPool.CurrentAmmo = AmmoPool.MaxAmmo;
	}
}

void ABaseEmpiresWeapon::Reload()
{
	if (GetTotalAmmo() <= 0) return; //We don't have any ammo to reload

	SCREENLOG(TEXT("Starting Reload"));

	//Get the current reload animation
	UAnimMontage* ReloadAnim = GetActiveWeaponAnimationSet().ReloadAnimation;
	float ReloadTime = GetAmmoPool().ReloadTime;

	if (ReloadAnim == nullptr)
	{
		PlayAnimation(ReloadAnim);
	}

	GetWorld()->GetTimerManager().SetTimer(this, &ABaseEmpiresWeapon::DoReload, ReloadTime, false);

	bReloading = true;
}

void ABaseEmpiresWeapon::DoReload()
{
	SCREENLOG(TEXT("Ending Reload"));

	int Idx = GetActiveFiremodeData().AmmoPoolIndex;


	if (AmmoPools[Idx].CurrentAmmo < AmmoPools[Idx].ClipSize) //We don't have enough ammo to fill out a full clip
	{
		AmmoPools[Idx].AmmoInClip = AmmoPools[Idx].CurrentAmmo; //So set the ammo to whatever is left
		AmmoPools[Idx].CurrentAmmo = 0;
	}
	else //Otherwise, max out our clip
	{
		//Figure out how many bullets we need
		int32 bulletsNeeded = AmmoPools[Idx].ClipSize - AmmoPools[Idx].AmmoInClip;

		//Max out the clip size
		AmmoPools[Idx].AmmoInClip = AmmoPools[Idx].ClipSize;
		//And take the diff from the pool
		AmmoPools[Idx].CurrentAmmo -= bulletsNeeded;
	}
	bReloading = false;
	
}

FVector ABaseEmpiresWeapon::AdjustByCof(FVector Aim)
{
	//Get the current cone of fire

	FWeaponRecoilData recoilData = GetCurrentRecoilData();

	/* CONE OF FIRE CALC
	BaseCof is the default cone of fire for the first shot.
	BloomModifier is how much the cone of fire blooms per shot.
	MaxCoF is the maximum value that the cone can get to.

	Cone Angle is calculated as:

	ActualCoF = BaseCof	+ (BloomModifier * NumberOfShots)

	Cone of Fire will always be BaseCoF < ActualCoF < MaxCoF
	*/

	float BaseCof = 0;
	float BloomModifier = 0;
	float MaxCof = recoilData.MaxStand;


	//TODO: Get movementstate
	//TODO: Get Standing/Crouching/Prone
	//TODO: Get ADS or Hip
	if (OwningCharacter->IsMoving())
	{
		BaseCof = recoilData.StandHipMove;
		BloomModifier = recoilData.StandingHipBloom;
	}
	else
	{
		BaseCof = recoilData.StandHipStill;
	}


	//Add cof bloom
	float AdjustedBloom = FMath::Min((BaseCof + (BloomModifier * ShotsFired)), MaxCof);


	return FMath::VRandCone(Aim, FMath::DegreesToRadians(AdjustedBloom / 2));

}
float ABaseEmpiresWeapon::RollVerticalRecoil()
{

	FWeaponRecoilData recoilData = GetCurrentRecoilData();
	
	float minRecoil = recoilData.VerticalRecoilMin;
	float maxRecoil = recoilData.VerticalRecoilMax;


	float recoilVal = FMath::FRandRange(minRecoil, maxRecoil);

	float recoilMultiplier = 1;
	
	//TODO: Get stance
	recoilMultiplier = recoilData.StandingRecoilMultiplier;

	if (ShotsFired == 0) recoilMultiplier += recoilData.FirstShotRecoilMultiplier;

	return recoilVal * recoilMultiplier;
}
float ABaseEmpiresWeapon::RollHorizontalRecoil()
{
	

	FWeaponRecoilData recoilData = GetCurrentRecoilData();
	//If Left and right recoil are both false, we don't horizontal recoil
	if (!recoilData.LeftRecoils && !recoilData.RightRecoils) return 0;


	float minRecoil = recoilData.HorizontalRecoilMin;
	float maxRecoil = recoilData.HorizontalRecoilMax;
	bool recoilRight = true;


	//Figure out if we are recoiling right or left
	if (recoilData.LeftRecoils && recoilData.RightRecoils) //If they are both true, pick a random recoil direction
	{
		recoilRight = (FMath::Rand() % 2) == 0;
	}
	else if (recoilData.LeftRecoils && !recoilData.RightRecoils) //If left is true and right is false, always recoil left
	{
		recoilRight = false;
	}
	//By default we recoil right

	float recoilVal = FMath::FRandRange(minRecoil, maxRecoil);

	//Scale the recoil direction by the biases
	if (recoilRight)
	{
		recoilVal *= recoilData.RightRecoilBias;
	}
	else
	{
		recoilVal *= recoilData.LeftRecoilBias;
		recoilVal = -recoilVal; //Invert the recoil direction
	}


	float recoilMultiplier = 1;

	//TODO: Get stance
	recoilMultiplier = recoilData.StandingRecoilMultiplier;

	if (ShotsFired == 0) recoilMultiplier += recoilData.FirstShotRecoilMultiplier;

	return recoilVal * recoilMultiplier;
}