// Fill out your copyright notice in the Description page of Project Settings.

#include "Empires2.h"
#include "EmpiresPlayerState.h"
#include "UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "InfantryClass.h"
#include "BaseInfantryWeapon.h"

AEmpiresPlayerState::AEmpiresPlayerState(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bReplicates = true;
}

void AEmpiresPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		Inventory = NewObject<UBaseEmpiresInventory>(this);
				
		SelectClass(DefaultClass);
	}
}

void AEmpiresPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEmpiresPlayerState, Inventory);
	DOREPLIFETIME(AEmpiresPlayerState, CurrentClass);

}

bool AEmpiresPlayerState::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool Wrote = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (Inventory != nullptr)
	{
		Wrote |= Channel->ReplicateSubobject(Inventory, *Bunch, *RepFlags);
	}	

	return Wrote;
}

void AEmpiresPlayerState::SelectClass(TAssetPtr<UInfantryClass> Class)
{
	if (Class.IsNull()) return;

	

	Inventory->ClearInventory();

	CurrentClass = Class;
	ABaseInfantryWeapon* Pistol = GetWorld()->SpawnActor<ABaseInfantryWeapon>(CurrentClass->Pistol);
	Inventory->AddItem(EInfantryInventorySlots::Slot_Sidearm, Pistol);

	ABaseInfantryWeapon* Rifle = GetWorld()->SpawnActor<ABaseInfantryWeapon>(CurrentClass->Primary);
	Inventory->AddItem(EInfantryInventorySlots::Slot_Primary, Rifle);

}