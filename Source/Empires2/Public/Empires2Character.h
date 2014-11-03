// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "InfantryInventory.h"
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

protected:

	void BeginPlay() override;


	/** Handler for a touch input beginning. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
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

	class AEmpiresPlayerState* GetEmpiresPlayerState()
	{
		return Cast<AEmpiresPlayerState>(this->GetController()->PlayerState);
	}

	//WEAPONS
public:
	void DrawWeapon(UBaseInfantryWeapon* Weapon);

	void SwitchToWeapon(EInfantryInventorySlots::Type Weapon);


	/* Weapon Input Events*/
	void SelectNextWeapon();
	void SelectPreviousWeapon();
	void SelectLastWeapon();

protected:
		
	EInfantryInventorySlots::Type SelectedWeapon;

	EInfantryInventorySlots::Type LastSelectedWeapon;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
};

