// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Empires2.h"
#include "Empires2Character.h"
#include "BulletProjectile.h"
#include "BaseInfantryWeapon.h"
#include "EmpiresPlayerState.h"
#include "InfantryInventory.h"
#include "Animation/AnimInstance.h"


//////////////////////////////////////////////////////////////////////////
// AEmpires2Character

AEmpires2Character::AEmpires2Character(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	WeaponRelativeOffset = FVector(0, 0, -85.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = CapsuleComponent;
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->RelativeLocation = FVector(0.f, 0.f, -150.f);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

}


void AEmpires2Character::BeginPlay()
{
	AEmpiresPlayerState* playerState = Cast<AEmpiresPlayerState>(this->GetController()->PlayerState);
	check(playerState);



	for (int32 i = 0; i < playerState->Inventory.Weapons.Num(); i++)
	{
		UBaseInfantryWeapon* Weap = ConstructObject<UBaseInfantryWeapon>(playerState->Inventory.Weapons[i]);
		Weap->SetOwner(this);
		playerState->Inventory.ConstructedWeapons.Add(Weap);
	}

	SwitchToWeapon(EInfantryInventorySlots::Slot_Primary);


	Super::BeginPlay();
}


//////////////////////////////////////////////////////////////////////////
// Input

void AEmpires2Character::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AEmpires2Character::BeginFire);
	InputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &AEmpires2Character::EndFire);


	//Weapon Selection
	InputComponent->BindAction("NextWeapon", IE_Pressed, this, &AEmpires2Character::SelectNextWeapon);
	InputComponent->BindAction("PreviousWeapon", IE_Pressed, this, &AEmpires2Character::SelectPreviousWeapon);
	InputComponent->BindAction("LastWeapon", IE_Pressed, this, &AEmpires2Character::SelectLastWeapon);
	InputComponent->BindAction("ChangeFiremode", EInputEvent::IE_Pressed, this, &AEmpires2Character::ChangeFiremode);


	//Movement
	InputComponent->BindAxis("MoveForward", this, &AEmpires2Character::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AEmpires2Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AEmpires2Character::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AEmpires2Character::LookUpAtRate);
}


////////////////////////////////// MOVEMENT
void AEmpires2Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AEmpires2Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AEmpires2Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AEmpires2Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

//////////////////////////////////////FIRE CONTROL

void AEmpires2Character::BeginFire()
{
	UBaseInfantryWeapon* Weapon = GetActiveWeapon();
	if (Weapon == nullptr) return; //No weapon? Don't bother firing

	Weapon->BeginFire();

}
void AEmpires2Character::EndFire()
{
	UBaseInfantryWeapon* Weapon = GetActiveWeapon();
	check(Weapon); //If the weapon goes null while we are firing... uh, crash

	Weapon->EndFire();
}

////////////////////////////////////////////WEAPONS

UBaseInfantryWeapon* AEmpires2Character::GetActiveWeapon()
{
	AEmpiresPlayerState* playerState = GetEmpiresPlayerState();
	check(playerState);
	return playerState->Inventory.ConstructedWeapons[this->SelectedWeapon];
}

void AEmpires2Character::DrawWeapon(UBaseInfantryWeapon* Weapon)
{
	// Get the animation object for the arms mesh
	UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();

	//If the weapon is null, hide the view model
	if (Weapon == nullptr)
	{
		Mesh1P->SetHiddenInGame(true);
		return;
	}
	else //If it's not
	{
		Mesh1P->SetHiddenInGame(false);
	}


	//Set the mesh to be the weapon we have
	Mesh1P->SetSkeletalMesh(Weapon->ViewModel);
	Mesh1P->SetAnimation(Weapon->FireAnimation);

	if (Weapon->DrawWeaponAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(Weapon->DrawWeaponAnimation, 1.f);
		}
	}

}

void AEmpires2Character::SwitchToWeapon(EInfantryInventorySlots::Type Weapon)
{
	AEmpiresPlayerState* playerState = GetEmpiresPlayerState();
	check(playerState);

	if (playerState->Inventory.ConstructedWeapons.Num() <= Weapon) return; //Trying to select an out of bounds weapon	
	if (!playerState->Inventory.ConstructedWeapons[Weapon])
	{
		this->LastSelectedWeapon = this->SelectedWeapon;
		this->SelectedWeapon = EInfantryInventorySlots::Slot_None;
		DrawWeapon(nullptr); //Trying to get a null weapon
		return;
	}
	if (!playerState->Inventory.ConstructedWeapons[Weapon]->GetClass()->IsChildOf(UBaseInfantryWeapon::StaticClass())) return; //Not an infantry weapon


	this->LastSelectedWeapon = this->SelectedWeapon;
	UBaseInfantryWeapon* Weap = playerState->Inventory.ConstructedWeapons[Weapon];
	DrawWeapon(Weap);
	this->SelectedWeapon = Weapon;

}

void AEmpires2Character::SelectNextWeapon()
{
	AEmpiresPlayerState* playerState = GetEmpiresPlayerState();
	check(playerState);

	//Increment the slot
	int32 Slot = this->SelectedWeapon + 1;
	//If the slot is greater than the number of weapons, reset it
	if (playerState->Inventory.ConstructedWeapons.Num() <= Slot)
	{
		Slot = EInfantryInventorySlots::Slot_Sidearm;
	}
	SwitchToWeapon((EInfantryInventorySlots::Type)Slot);

}
void AEmpires2Character::SelectPreviousWeapon()
{
	AEmpiresPlayerState* playerState = GetEmpiresPlayerState();
	check(playerState);

	//Increment the slot
	int32 Slot = this->SelectedWeapon - 1;
	//If the number is less than 0, set it to the max weapon
	if (Slot < 0)
	{
		Slot = playerState->Inventory.ConstructedWeapons.Num() - 1;
	}
	SwitchToWeapon((EInfantryInventorySlots::Type)Slot);
}
void AEmpires2Character::SelectLastWeapon()
{
	SwitchToWeapon(this->LastSelectedWeapon);
}

void AEmpires2Character::ChangeFiremode()
{
	UBaseInfantryWeapon* Weapon = GetActiveWeapon();
	if (Weapon == nullptr) return; //No weapon? Don't bother chaning firemode

	Weapon->NextFiremode();
}