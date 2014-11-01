// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"

#include "BulletProjectile.h"
#include "BaseEmpiresWeapon.generated.h"

USTRUCT()
struct FEmpDamageInfo : public FDamageEvent
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=General)
	float Damage;
	
};


/**
 * 
 */
UCLASS(Blueprintable)
class EMPIRES2_API UBaseEmpiresWeapon : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	void OnFire();

	void SetOwner(class AEmpires2Character* Owner);

	AEmpires2Character* OwningCharacter;

	UPROPERTY(EditDefaultsOnly, Category = Display)
	USkeletalMesh* ViewModel;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABaseEmpiresProjectile> ProjectileClass;
	
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display)
	class UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		FVector GunOffset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Projectile)
	FEmpDamageInfo DamageInfo;

};
