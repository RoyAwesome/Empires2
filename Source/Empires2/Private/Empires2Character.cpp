// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Empires2.h"
#include "Empires2Character.h"
#include "BulletProjectile.h"
#include "BaseInfantryWeapon.h"
#include "EmpiresPlayerState.h"
#include "BaseEmpiresInventory.h"
#include "Engine/ActorChannel.h"
#include "Animation/AnimInstance.h"
#include "UnrealNetwork.h"
#include "InfantryClass.h"

//////////////////////////////////////////////////////////////////////////
// AEmpires2Character

AEmpires2Character::AEmpires2Character(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	this->bAlwaysRelevant = true;
	this->bReplicates = true;

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
	if (Role == ROLE_Authority)
	{
		Inventory = PCIP.CreateDefaultSubobject<UBaseEmpiresInventory>(this, TEXT("Inventory"));
		Inventory->SetNetAddressable();
		Inventory->SetIsReplicated(true);

	}

	RevivePercent = .5f;
	MaxHealth = 1000;
	DisableReviveTime = 10;
}


void AEmpires2Character::BeginPlay()
{	
	Super::BeginPlay();
		
}

void AEmpires2Character::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	if (Role == ROLE_Authority && Controller)
	{	
		SpawnInventory();	
	}

}

void AEmpires2Character::PostInitProperties()
{
	Super::PostInitProperties();

	SetHealth(MaxHealth);

}

void AEmpires2Character::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEmpires2Character, SelectedWeapon);
	DOREPLIFETIME(AEmpires2Character, LastSelectedWeapon);
	DOREPLIFETIME(AEmpires2Character, Health);
	DOREPLIFETIME(AEmpires2Character, LastReviveTime);
	DOREPLIFETIME(AEmpires2Character, LastDeathTime);

	DOREPLIFETIME(AEmpires2Character, bCanRevive);
	DOREPLIFETIME(AEmpires2Character, bIsDead);

		
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
	InputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &AEmpires2Character::ReloadWeapon);


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
	ABaseInfantryWeapon* Weap = GetActiveWeapon();
	if (Weap == nullptr) return; //No weapon? Don't bother firing

	bIsFiring = true;
	Weap->BeginFire();

}
void AEmpires2Character::EndFire()
{
	if (!bIsFiring) return; //If we aren't firing our weapon, don't bother ending

	ABaseInfantryWeapon* Weapon = GetActiveWeapon();
	check(Weapon); //If the weapon goes null while we are firing... uh, crash

	Weapon->EndFire();
	bIsFiring = false;
}

////////////////////////////////////////////WEAPONS

ABaseInfantryWeapon* AEmpires2Character::GetActiveWeapon()
{
	ABaseEmpiresWeapon* Weap = Inventory->GetItemInSlot((EInfantryInventorySlots::Type)SelectedWeapon);
	return Cast<ABaseInfantryWeapon>(Weap);	
}

void AEmpires2Character::DrawWeapon(ABaseInfantryWeapon* Weapon)
{
	

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

	Weapon->Equip();
	

}


void AEmpires2Character::SwitchToWeapon(EInfantryInventorySlots::Type Weapon)
{
		
	if (Inventory->GetInventorySize() <= Weapon) return; //Trying to select an out of bounds weapon	

	ABaseInfantryWeapon* Weap = Cast<ABaseInfantryWeapon>(Inventory->GetItemInSlot(Weapon));

	if (Weap == nullptr)
	{
		if (Role == ROLE_Authority)
		{
			this->LastSelectedWeapon = this->SelectedWeapon;
			this->SelectedWeapon = EInfantryInventorySlots::Slot_None;
		}
	
		DrawWeapon(nullptr); //Trying to get a null weapon
		return;
	}

	if(Role == ROLE_Authority) this->LastSelectedWeapon = this->SelectedWeapon;
	
	DrawWeapon(Weap);
	this->SelectedWeapon = Weapon;	

}


void AEmpires2Character::RefreshHeldWeapon()
{
	ABaseInfantryWeapon* Weap = Cast<ABaseInfantryWeapon>(Inventory->GetItemInSlot(SelectedWeapon));
	DrawWeapon(Weap);
}


void AEmpires2Character::SelectNextWeapon()
{	
	if (Role < ROLE_Authority)
	{
		ServerSelectNextWeapon();
	}
	//Increment the slot
	int32 Slot = this->SelectedWeapon + 1;
	//If the slot is greater than the number of weapons, reset it
	if (Slot > (int32)EInfantryInventorySlots::Slot_Tertiary)
	{
		Slot = (int32)EInfantryInventorySlots::Slot_Sidearm;
	}
	
	TRACE("Switched to slot %d", Slot);
	SwitchToWeapon((EInfantryInventorySlots::Type)Slot);
	

}
void AEmpires2Character::SelectPreviousWeapon()
{
	if (Role < ROLE_Authority)
	{
		ServerSelectPreviousWeapon();
	}

	//Increment the slot
	int32 Slot = this->SelectedWeapon - 1;
	//If the number is less than 0, set it to the max weapon
	if (Slot < (int32)EInfantryInventorySlots::Slot_Sidearm)
	{
		Slot = (int32)EInfantryInventorySlots::Slot_Tertiary;
	}
	TRACE("Switched to slot %d", Slot);
	SwitchToWeapon((EInfantryInventorySlots::Type)Slot);
	
}
void AEmpires2Character::SelectLastWeapon()
{
	if (Role < ROLE_Authority)
	{
		ServerSelectLastWeapon();
	}
	SwitchToWeapon(this->LastSelectedWeapon);
}


void AEmpires2Character::OnRep_SelectedWeapon()
{
	SwitchToWeapon(SelectedWeapon);
}



void AEmpires2Character::ChangeFiremode()
{
	
	ABaseInfantryWeapon* Weapon = GetActiveWeapon();
	if (Weapon == nullptr) return; //No weapon? Don't bother changing firemode

	Weapon->NextFiremode();
}

void AEmpires2Character::ReloadWeapon()
{
	ABaseInfantryWeapon* Weapon = GetActiveWeapon();
	if (Weapon == nullptr) return; //No weapon? Don't bother reloading

	Weapon->Reload();
}


void AEmpires2Character::ServerSelectNextWeapon_Implementation()
{
	SelectNextWeapon();
}
bool AEmpires2Character::ServerSelectNextWeapon_Validate()
{
	return true;
}

void AEmpires2Character::ServerSelectPreviousWeapon_Implementation()
{
	this->SelectPreviousWeapon();
}
bool AEmpires2Character::ServerSelectPreviousWeapon_Validate()
{
	return true;
}

void AEmpires2Character::ServerSelectLastWeapon_Implementation()
{
	SelectLastWeapon();
}
bool AEmpires2Character::ServerSelectLastWeapon_Validate()
{
	return true;
}

void AEmpires2Character::PickupWeapon(EInfantryInventorySlots::Type Slot, ABaseEmpiresWeapon* Weapon)
{
	if (Role < ROLE_Authority) return; //Only the server can pick up a weapon
	if (Weapon == nullptr) return;

	Weapon->SetOwner(this);
		
	Inventory->AddItem(Slot, Weapon);
}


void AEmpires2Character::SpawnInventory()
{
	if (Role < ROLE_Authority)
	{
		return;
	}

	//Clear the inventory
	Inventory->ClearInventory();

	AEmpiresPlayerState* playerState = GetEmpiresPlayerState();
	if (!playerState) return;

	//Add the primary and secondary weapons
	ABaseEmpiresWeapon* Pistol = GetWorld()->SpawnActor<ABaseEmpiresWeapon>(playerState->DefaultClass->Pistol);
	Pistol->SetOwner(this);
	Inventory->AddItem(EInfantryInventorySlots::Slot_Sidearm, Pistol);

	ABaseEmpiresWeapon* Rifle = GetWorld()->SpawnActor<ABaseEmpiresWeapon>(playerState->DefaultClass->Primary);
	Rifle->SetOwner(this);
	Inventory->AddItem(EInfantryInventorySlots::Slot_Primary, Rifle);

	SwitchToWeapon(EInfantryInventorySlots::Slot_Primary);
	
}

//Destroy this character so that we can spawn a new character for him later.  
void AEmpires2Character::Respawn()
{
	Inventory->ClearInventory();
	//Start destroying this character

	Destroy();
}

void AEmpires2Character::Die(AController* Instigator, bool CanRevive)
{
	bIsDead = true;
	bCanRevive = CanRevive;
	LastDeathTime = GetWorld()->TimeSeconds;


	//TODO: Play the death animation and then ragdoll

	//Remove controls
	if(InputComponent) InputComponent->Deactivate();

	//Show the death screen
	AEmpiresPlayerController* EmpController = Cast<AEmpiresPlayerController>(GetController());
	EmpController->NotifyDied(Instigator, CanRevive);

}

void AEmpires2Character::Revive()
{
	//Give controls back
	if (InputComponent) InputComponent->Activate();
	bIsDead = false;


	//Remove the death screen

	//Play the get up animation

	//Set health to 1/2 max health
	SetHealth(MaxHealth * RevivePercent);
}

float AEmpires2Character::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float RealDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (RealDamage == 0) return 0;

	//TODO: Friendly Fire Y/N?

	//TODO: Resistances

	float Health = GetHealth() - RealDamage;

	AEmpiresPlayerController* EmpController = Cast<AEmpiresPlayerController>(GetController());
	EmpController->NotifyWasHit(EventInstigator, RealDamage, DamageEvent);

	AEmpiresPlayerController* OtherController = Cast<AEmpiresPlayerController>(EventInstigator);
	OtherController->NotifyLandedHit(this);

	if (Health <= 0)
	{
		//Die
		Die(EventInstigator, true); //TODO: Test to see if we can revive
	}

	SetHealth(Health);



	return RealDamage;
}

void AEmpires2Character::SetHealth(float amount)
{
	Health = amount;
}

float AEmpires2Character::GetHealth()
{
	return Health;
}
