// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "BaseEmpiresInventory.h"
#include "EmpiresPlayerState.h"
#include "Empires2Character.generated.h"




UCLASS(config=Game)
class AEmpires2Character : public ACharacter
{
	GENERATED_UCLASS_BODY()
			
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class UCameraComponent> FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Weapon)
	FVector WeaponRelativeOffset;
	

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	TSubobjectPtr<class USkeletalMeshComponent> Mesh1P;

public:
	bool IsMoving()
	{
		return bIsMoving;
	}

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

protected:
	UPROPERTY(VisibleAnywhere, Replicated, ReplicatedUsing = OnRep_SelectedWeapon, Category=Inventory)
	TEnumAsByte<EInfantryInventorySlots::Type> SelectedWeapon;
	UPROPERTY(VisibleAnywhere, Replicated, Category = Inventory)
	TEnumAsByte<EInfantryInventorySlots::Type> LastSelectedWeapon;



	UPROPERTY()
	bool bIsFiring;

	UPROPERTY(VisibleAnywhere, Replicated, Category=General)
	TSubobjectPtr<class UBaseEmpiresInventory> Inventory;


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

protected: 
	virtual void SpawnInventory();


	////////////// GAME FLOW
	public:

		void Respawn();
		void Die();
		void Revive();


};

