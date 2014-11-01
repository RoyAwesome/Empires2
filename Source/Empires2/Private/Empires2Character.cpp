// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Empires2.h"
#include "Empires2Character.h"
#include "BulletProjectile.h"
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


	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	
}


void AEmpires2Character::BeginPlay()
{
	if (Weapon == nullptr)
	{
		if (!WeaponClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("No WeaponClass Set!"))
				return;
		}
		//Create a weapon for us
		UWorld* const World = GetWorld();
		Weapon = World->SpawnActor<ABaseEmpiresWeapon>(WeaponClass);
		Weapon->SetOwner(this);
		Weapon->SetActorRelativeLocation(WeaponRelativeOffset);
		Weapon->AttachRootComponentTo(CapsuleComponent, NAME_None, EAttachLocation::SnapToTarget);

	}
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
	
	InputComponent->BindAction("Fire", IE_Pressed, this, &AEmpires2Character::OnFire);
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AEmpires2Character::TouchStarted);

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

void AEmpires2Character::OnFire()
{
	if (Weapon == nullptr)
	{
		return;
	}
	
	Weapon->OnFire();

}

void AEmpires2Character::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// only fire for first finger down
	if (FingerIndex == 0)
	{
		OnFire();
	}
}

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
