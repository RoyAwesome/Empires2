// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "BaseEmpiresWeapon.generated.h"

const int32 CurrentAmmopool = -1;
const int32 CurrentFiremode = -1;

//Weapon State Enums
//NotEquipped: Weapon is not attached to any character, and GetOwningCharacter() returns null
//Equipping: Weapon is going into the inventory. 
//NotSelected: Weapon is in the inventory, but not the active weapon
//Drawing: Weapon is being pulled out to use
//Idle: Weapon is in hand
//Firing: Weapon is being fired
//Reloading: Weapon is being reloaded. 
UENUM()
namespace EWeaponState
{
	enum Type
	{
		Weapon_NotEquipped,
		Weapon_Equipping,
		Weapon_NotSelected,
		Weapon_Drawing,
		Weapon_Idle,
		Weapon_Firing,
		Weapon_Reloading,
	};

}

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
	UPROPERTY(EditDefaultsOnly, Category = DataReferences)
	int32 RecoilDataIndex;


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

	UPROPERTY(EditDefaultsOnly, Category=General)
	float Damage;


	UPROPERTY(EditDefaultsOnly, Category = General)
	TSubclassOf<class UWeaponFireType> FireType;

	FAmmoPool()
	{
		MaxAmmo = 120;
		ClipSize = 30;	
		Damage = 143;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Particles)
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Particles)
	bool bMuzzleFlashLight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Particles)
	UParticleSystem* BulletEffect;
};

USTRUCT()
struct FWeaponRecoilData
{
	GENERATED_USTRUCT_BODY()
public:

	//RECOIL

	/*
		How much the gun kicks up in degrees max.  
		Actual recoil value will be between Min and Max Inclusive
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float VerticalRecoilMin;
	/* 
		How much the gun kicks up in degrees min.  
		Actual recoil value will be between Min and Max Inclusive
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float VerticalRecoilMax;

	/*		
		How much the gun kicks left or right in degrees max.
		Multipled by the Left or Right recoil bias.
		Actual recoil value will be between Min and Max Inclusive
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float HorizontalRecoilMin;
	/*
	How much the gun kicks left or right in degrees min.
	Multipled by the Left or Right recoil bias.
	Actual recoil value will be between Min and Max Inclusive
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float HorizontalRecoilMax;

	
	/*
	Indicates whether it is possible to recoil to the right
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		bool RightRecoils;
	/*
	Indicates whether it is possible to recoil to the left
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		bool LeftRecoils;

	/*
	Scales the recoil in the Right direction
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float RightRecoilBias;
	/*
	Scales the recoil in the Left direction
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float LeftRecoilBias;

	/*
		How much more the first shot recoils over consecutive shots.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float FirstShotRecoilMultiplier;

	/*
	Scales all recoils when standing
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float StandingRecoilMultiplier;
	/*
	Scales all recoils when crouching
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float CrouchingRecoilMultiplier;
	/*
	Scales all recoils when prone
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Recoil)
		float ProneRecoilMultiplier;


	//CONE OF FIRE
	/*
	How fast do you move when Aiming Down Sights, scaled from normal player movement
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MoveSpeed)
		float ADSMoveSpeedMultiplier;

	/*
	Default cone of fire when moving and firing from the hip
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float StandHipMove;
	/*
	Default cone of fire when standing and firing from the hip
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float StandHipStill;

	/*
	Default cone of fire when standing and moving while aiming down sights
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float StandADSMove;
	/*
	Default cone of fire when standing while aiming down sights
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float StandADSStill;
	/*
	Default cone of fire when crouching and moving
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float CrouchHipMove;
	/*
	Default cone of fire when crouching
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float CrouchHipStill;
	/*
	Default cone of fire when crouching and moving while aiming down sights
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float CrouchADSMove;
	/*
	Default cone of fire when crouching while aiming down sights
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float CrouchADSStill;

	/*
	Default cone of fire when prone and moving
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float ProneHipMove;
	/*
	Default cone of fire when prone
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float ProneHipStill;

	/*
	Default cone of fire when prone and moving while aiming down sights
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float ProneADSMove;
	/*
	Default cone of fire when prone while aiming down sights
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float ProneADSStill;

	/*
	How much the cone of fire blooms when standing per shot. 	
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float StandingHipBloom;
	/*
	How much the cone of fire blooms when crouching per shot.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float CrouchingHipBloom;
	/*
	How much the cone of fire blooms when prone per shot.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float ProneHipBloom;

	/*
	How much the cone of fire blooms when standing and aiming down sights per shot.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float StandingADSBloom;
	/*
	How much the cone of fire blooms when crouching and aiming down sights per shot.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float CrouchingADSBloom;
	/*
	How much the cone of fire blooms when prone and aiming down sights per shot.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float ProneADSBloom;

	/*
	How large can the cone of fire get while standing
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float MaxStand;
	/*
	How large can the cone of fire get while crouching
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float MaxCrouch;
	/*
	How large can the cone of fire get while prone
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ConeOfFire)
		float MaxProne;

	
	FWeaponRecoilData()
	{
		VerticalRecoilMin = .1f;
		VerticalRecoilMax = .15f;

		HorizontalRecoilMin = 0.25;
		HorizontalRecoilMin = 0.275;

		RightRecoils = true;
		LeftRecoils = false;

		RightRecoilBias = 1;
		LeftRecoilBias = 0;

		FirstShotRecoilMultiplier = 3;

		StandingRecoilMultiplier = 1;
		CrouchingRecoilMultiplier = .85f;
		ProneRecoilMultiplier = .70;

		ADSMoveSpeedMultiplier = .5f;

		StandHipMove = 2.25f;
		StandHipStill = 1.5f;

		StandADSMove = 0.35f;
		StandADSStill = 0.1f;

		CrouchHipMove = 1.75f;
		CrouchHipStill = 1.125f;

		CrouchADSMove = 0.2;
		CrouchADSStill = 0.1;

		ProneHipMove = 1.25f;
		ProneHipStill = .9f;

		ProneADSMove = 0.1f;
		ProneADSStill = 0.065f;

		StandingHipBloom = .1f;
		CrouchingHipBloom = .1f;
		ProneHipBloom = .1f;

		StandingADSBloom = 0.05f;
		CrouchingADSBloom = 0.05f;
		ProneADSBloom = 0.05f;

		MaxStand = 5 * StandHipStill;
		MaxCrouch = 5 * CrouchHipStill;
		MaxProne = 5 * ProneHipStill;
	}
};

/**
 * Base Weapon
 */
UCLASS()
class EMPIRES2_API ABaseEmpiresWeapon : public AActor
{
	GENERATED_BODY()
		//GENERAL
public:
	ABaseEmpiresWeapon(const class FObjectInitializer & ObjectInitializer);


	virtual void PostInitProperties() override;

	
	USkeletalMeshComponent* GetMesh1P() const
	{
		return Mesh1P;
	}

	USkeletalMeshComponent* GetMesh3P() const
	{
		return Mesh3P;
	}

private:
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh3P;

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
	UPROPERTY(Replicated)
	class AEmpires2Character* OwningCharacter;

	virtual void SetOwner(AEmpires2Character* Owner);

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		FVector GunOffset;

	virtual void Tick(float DeltaSeconds) override;

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


	///////// Serverside Input
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStartFire();

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerEndFire();
	
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerFireShot();


	
	UFUNCTION()
	void OnRep_Reload();


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
		FEmpDamageInfo DamageInfo; //TODO: Remove this, Let Ammo Pool Decide

	FVector GetFireDirection();

	void DealDamage(AEmpires2Character* Target);

protected:
	UPROPERTY(VisibleAnywhere, Category = General, Replicated, ReplicatedUsing=OnRep_WeaponState)
	TEnumAsByte<EWeaponState::Type> WeaponState;

	UFUNCTION()
	void OnRep_WeaponState();

	UFUNCTION(NetMulticast, Unreliable)
	void NotifyClientShotFired(FVector StartPoint, FRotator Direction);

	//Called on Clients and server to emit the shot.  
	void EmitShot(FVector StartPoint, FRotator Direction);

	void ClientPlayWeaponEffect(FVector StartPoint, FRotator Direction);


	UPROPERTY(Replicated)
	int32 ShotsFired;

	UPROPERTY(Replicated)
	int32 WeaponSeed;

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

	UPROPERTY(Replicated)
	TArray<int32> CurrentClipPool;
	UPROPERTY(Replicated)
	TArray<int32> RemainingAmmoPool;

	UPROPERTY(VisibleAnywhere, Category = Firemodes)
	TArray<UWeaponFireType*> Firetypes;

	UFUNCTION(BlueprintCallable, Category = Firemode)
		virtual FWeaponData GetActiveFiremodeData();

	UFUNCTION(BlueprintCallable, Category = Firemode)
		virtual UBaseFiremode* GetActiveFiremode();

	UFUNCTION(BlueprintCallable, Category = Firemode)
		virtual FAmmoPool GetCurrentAmmoPool();

	virtual UWeaponFireType* GetCurrentFiretype();

	void NextFiremode();

	virtual UBaseFiremode* GetFiremode(int32 Firemode);

	virtual FWeaponData GetFiremodeData(int32 Firemode);


protected:
	UPROPERTY()
	TArray<UBaseFiremode*> Firemodes;

	UPROPERTY(Replicated)
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



public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Firemodes)
		TArray<FWeaponRecoilData> RecoilData;

	FWeaponRecoilData GetCurrentRecoilData()
	{
		return RecoilData[GetActiveFiremodeData().RecoilDataIndex];
	}
protected:
	UPROPERTY(Replicated)
	float CurrentCoF;

	FVector AdjustByCof(FVector Aim);
	float RollVerticalRecoil();
	float RollHorizontalRecoil();

	/*  Play Weapon Effects */
	public: 



};
