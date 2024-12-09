// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGSaveGame.h"

URPGSaveGame::URPGSaveGame()
{
	SlotName = "Autosave";
	SlotNumber = 0;
	UserIndex = 0;
	SaveStats.WeaponName = TEXT("");
	SaveStats.MapName = TEXT("");
}

void URPGSaveGame::CreateSlot(int SaveSlotNumber)
{
	SlotName = CreateSaveSlotName(SaveSlotNumber);
	SlotNumber = SaveSlotNumber;
	UserIndex = 0;
}

void URPGSaveGame::CreateEmptySlot(int SaveSlotNumber)
{
	SlotName = "Empty Slot";
	SlotNumber = SaveSlotNumber;
	UserIndex = 0;
	SaveStats.WeaponName = TEXT("");
	SaveStats.MapName = TEXT("");
}

FString URPGSaveGame::CreateSaveSlotName(int SaveSlotNumber)
{
	if (SaveSlotNumber == 0)
	{
		return FString(("AutoSave"));
	}
	return FString(("Slot %d"), SaveSlotNumber);
}

FString URPGSaveGame::GetSlotName()
{
	return SlotName;
}
