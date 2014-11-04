// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "BaseEmpiresWeapon.generated.h"

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
	
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
		int32 AmmoPoolIndex;

	//FireBehavior
	UPROPERTY(EditDefaultsOnly, Category = Behavior)
		int32 RoundsPerMinute;
	UPROPERTY(EditDefaultsOnly, Category = Behavior)
		float FirstShotFireDelay;
	UPROPERTY(EditDefaultsOnly, Category = Behavior)
		int32 RoundsPerShot;
	


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
/**
 *
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
	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditDefaultsOnly, Category = Display)
		USkeletalMesh* ViewModel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
	USoundBase* ChangeFiremodeSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
	class UAnimMontage* ChangeFiremodeAnimation;

	///////////////// HELPERS
public:
	void PlaySound(USoundBase* Sound);

	void PlayAnimation(UAnimMontage* Animation);


public:
	class AEmpires2Character* OwningCharacter;

	void SetOwner(AEmpires2Character* Owner);

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		FVector GunOffset;

	//Shooting
public:
	virtual bool CanFire();

	void BeginFire();

	void EndFire();


	/*Called when the weapon is to fire a single bullet/projectile*/
	void FireShot();
	

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

	/*
		Firemodes.  They control how the gun fires
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Firemodes)
		TArray<TSubclassOf<class UBaseFiremode> > FiremodeClasses;

	FWeaponData GetActiveFiremodeData()
	{
		
		return FiremodeData[ActiveFiremode];
	}

	UBaseFiremode* GetActiveFiremode()
	{
		return Firemodes[ActiveFiremode];
	}

	FAmmoPool GetCurrentAmmoPool()
	{
		return AmmoPools[FiremodeData[ActiveFiremode].AmmoPoolIndex];
	}

	void NextFiremode();

protected:
	TArray<UBaseFiremode*> Firemodes;

	int32 ActiveFiremode;

};
