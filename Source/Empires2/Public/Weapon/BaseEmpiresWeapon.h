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
	UPROPERTY(EditDefaultsOnly, Category = General)
		float ReloadTime;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
		TSubclassOf<class ABaseEmpiresProjectile> ProjectileClass;


	UPROPERTY(BlueprintReadWrite, Category = Ammo)
		int32 CurrentAmmo;
	UPROPERTY(BlueprintReadWrite, Category = Ammo)
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

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
		UAnimMontage* ChangeFiremodeAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display)
		UAnimMontage* ReloadAnimation;

	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound)
	class USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound)
		USoundBase* ChangeFiremodeSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound)
		USoundBase* ReloadSound;
};




USTRUCT()
struct FWeaponRecoilData
{
	GENERATED_USTRUCT_BODY()
public:

	//RECOIL

	/*
		Vertical Recoil
		How much the gun kicks up when firing in Degrees
		*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float VerticalRecoilMin;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float VerticalRecoilMax;

	/*
		Horizontal Recoil.
		How much the gun kicks left or right in degrees.
		Multipled by the Left or Right recoil bias.
		*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float HorizontalRecoilMin;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float HorizontalRecoilMax;

	/*
		Possible to kick left or right.
		*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		bool RightRecoils;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		bool LeftRecoils;

	/*
		Multiplies agains the horizontal recoil max/min to scale down the different directional recoil
		*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float RightRecoilBias;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float LeftRecoilBias;

	/*
		How much the first shot recoils over consecutive shots
		*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float FirstShotRecoilMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float StandingRecoilMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float CrouchingRecoilMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float ProneRecoilMultiplier;


	//CONE OF FIRE
	/*
		How fast do you move while ADSing
		*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MoveSpeed)
		float ADSMoveSpeedMultiplier;

	/*
		Default cone of fire while standing and firing from the hip
		*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float StandHipMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float StandHipStill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float StandADSMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float StandADSStill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float CrouchHipMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float CrouchHipStill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float CrouchADSMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float CrouchADSStill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float ProneHipMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float ProneHipStill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float ProneADSMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float ProneADSStill;

	/*
		How much the cone of fire blooms when firing from these positions.  Multiplies by the related category above
		*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float StandingHipBloom;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float CrouchingHipBloom;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float ProneHipBloom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float StandingADSBloom;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float CrouchingADSBloom;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float ProneADSBloom;

	/*
		How large can the cone of fire get
		*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float MaxStand;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float MaxCrouch;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float MaxProne;

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

	UFUNCTION(BlueprintCallable, Category = Firemode)
		virtual FWeaponData GetActiveFiremodeData();

	UFUNCTION(BlueprintCallable, Category = Firemode)
		virtual UBaseFiremode* GetActiveFiremode();

	UFUNCTION(BlueprintCallable, Category = Firemode)
		virtual FAmmoPool GetCurrentAmmoPool();

	void NextFiremode();

	virtual UBaseFiremode* GetFiremode(int32 Firemode);

	virtual FWeaponData GetFiremodeData(int32 Firemode);


protected:
	TArray<UBaseFiremode*> Firemodes;

	int32 ActiveFiremode;


	//Ammo
public:
	virtual void ConsumeAmmo(int32 HowMuch = 1, int32 FromAmmoPool = CurrentAmmopool);

	//UFUNCTION(BlueprintCallable, Category = Firemode) //TODO: Figure out how to do default params with UFUNCTIONS
	virtual int32 GetAmmoInClip(int32 FromAmmoPool = CurrentAmmopool);

	//UFUNCTION(BlueprintCallable, Category = Firemode)
	virtual int32 GetTotalAmmo(int32 FromAmmoPool = CurrentAmmopool);

	virtual void AddAmmo(int32 Ammount, int32 ToAmmoPool = CurrentAmmopool);

	virtual void Reload();

	virtual void DoReload();

protected:
	FAmmoPool GetAmmoPool(int32 FromAmmoPool = CurrentAmmopool);

	bool bReloading;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Firemodes)
		TArray<FWeaponRecoilData> RecoilData;

};
