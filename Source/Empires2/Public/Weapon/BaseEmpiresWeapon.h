// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "BaseEmpiresWeapon.generated.h"

const int32 CurrentAmmopool = -1;
const int32 CurrentFiremode = -1;

USTRUCT()
struct FEmpDamageInfo : public FDamageEvent
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = General)
		float Damage;

};

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

public:

	//Ammo Info
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
		int32 AmmoConsumedPerShot;	

	//FireBehavior
	UPROPERTY(EditDefaultsOnly, Category = Behavior)
		int32 RoundsPerMinute;
	UPROPERTY(EditDefaultsOnly, Category = Behavior)
		float FirstShotFireDelay;
	UPROPERTY(EditDefaultsOnly, Category = Behavior)
		int32 RoundsPerShot;
	UPROPERTY(EditDefaultsOnly, Category = Behavior)
		TSubclassOf<class UBaseFiremode> FiremodeClass;

	//Indexes
	UPROPERTY(EditDefaultsOnly, Category = DataReferences)
		int32 AmmoPoolIndex;
	UPROPERTY(EditDefaultsOnly, Category = DataReferences)
		int32 AnimationSetIndex;


	//Damage
	UPROPERTY(EditDefaultsOnly, Category = Damage)
		int32 Damage;
	//TODO: Damage Type

	FWeaponData()
	{
		AmmoConsumedPerShot = 1;
		AmmoPoolIndex = 0;

		RoundsPerMinute = 600;
		FirstShotFireDelay = 0;
		RoundsPerShot = 1;

		Damage = 100;
	}

};

USTRUCT()
struct FAmmoPool
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = General)
	int32 MaxAmmo;
	UPROPERTY(EditDefaultsOnly, Category = General)
	int32 ClipSize;
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
		TSubclassOf<class ABaseEmpiresProjectile> ProjectileClass;

	int32 CurrentAmmo;
	int32 AmmoInClip;

	FAmmoPool()
	{
		MaxAmmo = 120;
		ClipSize = 30;

		CurrentAmmo = MaxAmmo;
		AmmoInClip = ClipSize;
	}

};

USTRUCT()
struct FWeaponAnimationSet
{
	GENERATED_USTRUCT_BODY()
public:
	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
		USoundBase* ChangeFiremodeSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
		UAnimMontage* ChangeFiremodeAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
		UAnimMontage* ReloadAnimation;
	
};

/**
 * Base Weapon
 */
UCLASS(Blueprintable)
class EMPIRES2_API UBaseEmpiresWeapon : public UObject
{
	GENERATED_UCLASS_BODY()
		//GENERAL
public:

	virtual void PostInitProperties() override;

	virtual UWorld* GetWorld() const override;

	//Display Properties
public:
	
	UPROPERTY(EditDefaultsOnly, Category = Display)
		USkeletalMesh* ViewModel;

	

	///////////////// HELPERS
public:
	virtual void PlaySound(USoundBase* Sound);

	virtual void PlayAnimation(UAnimMontage* Animation);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
	TArray<FWeaponAnimationSet> AnimationSets;

	virtual FWeaponAnimationSet GetActiveWeaponAnimationSet()
	{
		int32 idx = GetActiveFiremodeData().AnimationSetIndex;
		check(idx >= 0 && idx < AnimationSets.Num());
		return AnimationSets[idx];
	}


public:
	class AEmpires2Character* OwningCharacter;

	virtual void SetOwner(AEmpires2Character* Owner);

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		FVector GunOffset;

	//EQUIPPING
public:
	virtual void Equip();
	virtual void Unequip();



	//Shooting
public:
	virtual bool CanFire();

	virtual void BeginFire();

	virtual void EndFire();


	/*Called when the weapon is to fire a single bullet/projectile*/
	virtual void FireShot();
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
		FEmpDamageInfo DamageInfo; //TODO: Remove this, Let Ammo Pool Decide






	//Firemodes
public:
	/*
		Fire Data for the indivdual Firemode.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Firemodes)
		TArray<FWeaponData> FiremodeData;

	/*
		Number of ammo pools.  Each firemode references an ammo pool.  Useful for different firemodes that fire different projectile types
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Firemodes)
	TArray<FAmmoPool> AmmoPools;
		

	virtual FWeaponData GetActiveFiremodeData()
	{
		
		return FiremodeData[ActiveFiremode];
	}

	virtual UBaseFiremode* GetActiveFiremode()
	{
		return Firemodes[ActiveFiremode];
	}

	virtual FAmmoPool GetCurrentAmmoPool()
	{
		return AmmoPools[FiremodeData[ActiveFiremode].AmmoPoolIndex];
	}

	void NextFiremode();

	virtual UBaseFiremode* GetFiremode(int32 Firemode);

	virtual FWeaponData GetFiremodeData(int32 Firemode);


protected:
	TArray<UBaseFiremode*> Firemodes;

	int32 ActiveFiremode;


		//Ammo
public:
	virtual void ConsumeAmmo(int32 HowMuch = 1, int32 FromAmmoPool = CurrentAmmopool );

	virtual int32 GetAmmoInClip(int32 FromAmmoPool = CurrentAmmopool);

	virtual int32 GetTotalAmmo(int32 FromAmmoPool = CurrentAmmopool);

	virtual void AddAmmo(int32 Ammount, int32 ToAmmoPool = CurrentAmmopool);

	virtual void Reload(int32 AmmoPool = CurrentAmmopool);

protected:
		FAmmoPool GetAmmoPool(int32 FromAmmoPool);


};
