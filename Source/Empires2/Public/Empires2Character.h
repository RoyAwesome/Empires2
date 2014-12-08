// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "BaseEmpiresInventory.h"
#include "EmpiresPlayerState.h"
#include "Empires2Character.generated.h"




UCLASS(config=Game)
class AEmpires2Character : public ACharacter
{
	GENERATED_BODY()
public:
	AEmpires2Character(const class FObjectInitializer & ObjectInitializer);

private:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FirstPersonCameraComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

protected:


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Weapon)
	FVector WeaponRelativeOffset;

public:

	UCameraComponent* GetFirstPersonCamera() const
	{
		return FirstPersonCameraComponent;
	}

	USkeletalMeshComponent* Get1PMesh() const
	{
		return Mesh1P;
	}

	bool IsMoving()
	{
		return bIsMoving;
	}

	virtual void AddControllerPitchInput(float Rate) override;
	virtual void AddControllerYawInput(float Rate) override;

protected:


	void BeginPlay() override;
	void PossessedBy(AController * NewController) override;
	void PostInitProperties() override;
		
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	bool bIsMoving;

	class AEmpiresPlayerState* GetEmpiresPlayerState()
	{
		return Cast<AEmpiresPlayerState>(this->GetController()->PlayerState);
	}

	UPROPERTY(Replicated)
	bool bShouldIgnoreInput;

	//WEAPONS
public:
	//Firing the weapon
	void BeginFire();
	void EndFire();

	/* Switching Weapons */
	void DrawWeapon(class ABaseInfantryWeapon* Weapon);
	void SwitchToWeapon(EInfantryInventorySlots::Type Weapon);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	ABaseInfantryWeapon* GetActiveWeapon();

	/* Weapon Input Events */
	void SelectNextWeapon();	
	void SelectPreviousWeapon();
	void SelectLastWeapon();
	void ChangeFiremode();
	void ReloadWeapon();

	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSelectNextWeapon();
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSelectPreviousWeapon();
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSelectLastWeapon();
	
	/* End Weapon Input Events */

	

	void PickupWeapon(EInfantryInventorySlots::Type Slot, class ABaseEmpiresWeapon* Weapon);

	UFUNCTION()
	void OnRep_SelectedWeapon();

	void RefreshHeldWeapon();

	FName GetWeaponAttachSocket();

protected:
	UPROPERTY(VisibleAnywhere, Replicated, ReplicatedUsing = OnRep_SelectedWeapon, Category=Inventory)
	TEnumAsByte<EInfantryInventorySlots::Type> SelectedWeapon;
	UPROPERTY(VisibleAnywhere, Replicated, Category = Inventory)
	TEnumAsByte<EInfantryInventorySlots::Type> LastSelectedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName WeaponAttachSocket;

	UPROPERTY()
	bool bIsFiring;

	UBaseEmpiresInventory* GetInventory() const
	{
		return Inventory;
	}

private:
	UPROPERTY(VisibleAnywhere, Replicated, Category=General)
	class UBaseEmpiresInventory* Inventory;
		

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

protected: 
	virtual void SpawnInventory();


	////////////// GAME FLOW
public:

		virtual void Respawn();
		virtual void Die(AController* Instigator, bool CanRevive);
		virtual void ClientDie(); //Client side death related stuff.
		virtual void Revive();

		virtual void SetHealth(float amount);
		virtual float GetHealth();

		virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GameFlow, Replicated)
		bool bIsDead;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameFlow, Replicated)
		bool bCanRevive;
		
		UPROPERTY(Replicated)
		float LastReviveTime;

		UPROPERTY(Replicated)
			float LastDeathTime;



protected:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category=GameFlow)
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameFlow)
	float MaxHealth;
	
	/* How much of MaxHealth do you revive with */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameFlow)
	float RevivePercent;

	/* If you die within this amount of time since your last revive, you cannot revive */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=GameFlow)
	float DisableReviveTime;
};

