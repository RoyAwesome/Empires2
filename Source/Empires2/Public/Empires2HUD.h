// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "UMG.h"
#include "Empires2HUD.generated.h"

UCLASS()
class AEmpires2HUD : public AHUD
{
	GENERATED_UCLASS_BODY()

public:

	virtual void BeginPlay() override;


	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;


	/** Crosshair asset pointer */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crosshair)
	class UTexture2D* CrosshairTex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EventElements)
	TSubclassOf<class UUserWidget> DeathScreenWidget;
	
	UPROPERTY()
	UUserWidget* DeathScreen;

	UFUNCTION(BlueprintImplementableEvent, Category=HudEvents)
	void NotifyTookDamage(FVector FromWhere, int32 HowMuch, APlayerState* FromWho);
private:
	
};

