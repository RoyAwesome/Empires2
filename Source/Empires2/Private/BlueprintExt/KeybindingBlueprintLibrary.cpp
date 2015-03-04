// Copyright 2015 Infinite Machine Studios

#include "Empires2.h"
#include "KeybindingBlueprintLibrary.h"



FKey UKeybindingBlueprintLibrary::GetKey(FName Text)
{
	return FKey(Text);
}

FDGInputMapping UKeybindingBlueprintLibrary::GetKeybindForEvent(const FKeyEvent& KeyEvent)
{
	FDGInputMapping Input;

	Input.Key = KeyEvent.GetKey();
	Input.bAlt = KeyEvent.IsAltDown();
	Input.bCtrl = KeyEvent.IsControlDown();
	Input.bShift = KeyEvent.IsShiftDown();
	Input.bCmd = KeyEvent.IsCommandDown();

	return Input;
}

void UKeybindingBlueprintLibrary::GetAllKeyBindings(TArray<FDGInputMapping>& Bindings)
{
	Bindings.Empty();

	const UInputSettings* Settings = GetDefault<UInputSettings>();
	if (!Settings) return;

	const TArray<FInputActionKeyMapping>& Actions = Settings->ActionMappings;

	for (const FInputActionKeyMapping& Each : Actions)
	{
		Bindings.Add(FDGInputMapping(Each));
	}
}

void UpdateActionMapping(FInputActionKeyMapping& Current, FDGInputMapping Bind)
{
	Current.Key = Bind.Key;
	Current.bAlt = Bind.bAlt;
	Current.bCmd = Bind.bCmd;
	Current.bCtrl = Bind.bCtrl;
	Current.bShift = Bind.bShift;
}

bool UKeybindingBlueprintLibrary::RebindKey(FDGInputMapping Action)
{
	UInputSettings* Settings = GetMutableDefault<UInputSettings>();
	if (!Settings) return false;

	TArray<FInputActionKeyMapping>& Actions = Settings->ActionMappings;

	bool Found = false;

	for (int i = 0; i < Actions.Num(); i++)
	{
		FInputActionKeyMapping& act = Actions[i];
		if (act.ActionName == Action.ActionName)
		{
			//Change the action mapping to the new one
			UpdateActionMapping(act, Action);


			//Save the keybinds to Input.ini
			const_cast<UInputSettings*>(Settings)->SaveKeyMappings();

			//And rebuild it
			for (TObjectIterator<UPlayerInput> It; It; ++It)
			{
				It->ForceRebuildingKeyMaps(true);
			}
			return true;
		}
	}

	return false;

}
