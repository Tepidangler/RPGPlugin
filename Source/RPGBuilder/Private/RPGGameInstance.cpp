// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameInstance.h"
#include "RPGSaveGame.h"
#include "CharacterBase.h"
#include "RPGPlayerController.h"
#include "WeaponBase.h"
#include "ArmorBase.h"
#include "InventoryComponent.h"
#include "StatsComponent.h"
#include "PartySystem.h"
#include "ItemBase.h"
#include "Kismet/GameplayStatics.h"

URPGGameInstance::URPGGameInstance()
{

}



void URPGGameInstance::Init()
{
	Super::Init();
}

void URPGGameInstance::BeginPlay()
{
	SavedGameArray.Reserve(MaxSaveSlots);
	for (int i = 0; i <= 13; ++i)
	{
		if (UGameplayStatics::DoesSaveGameExist(FString(("Slot %d"), i), 0))
		{
			URPGSaveGame* LoadGameInstance = Cast<URPGSaveGame>(UGameplayStatics::LoadGameFromSlot(FString(("Slot %d"), i), 0));
			SavedGameArray.Insert(LoadGameInstance, i);

		}
	}

}

void URPGGameInstance::PostInitProperties()
{
	Super::PostInitProperties();

	if (GetWorld())
	{
		BeginPlay();
	}
}

bool URPGGameInstance::ParseDate(const FString& DateTimeString, FString& OutDate)
{
	TArray<FString> StringArray;
	FString FixedString = DateTimeString.Replace(TEXT("-"), TEXT(" "));
	FixedString.ReplaceInline(TEXT(":"), TEXT(" "), ESearchCase::CaseSensitive);
	FixedString.ReplaceInline(TEXT("."), TEXT("/"), ESearchCase::CaseSensitive);

	FixedString.ParseIntoArray(StringArray, TEXT(" "), true);

	if ((StringArray.Num() < 2 || StringArray.Num() == 0))
	{
		return false;
	}

	for (int32 i = 0; i < (StringArray.Num() - 1); ++i)
	{
		OutDate.Append(StringArray[i]);
	}

	return true;
}

bool URPGGameInstance::ParseTime(const FString& DateTimeString, FString& OutTime)
{
	TArray<FString> StringArray;
	FString FixedString = DateTimeString.Replace(TEXT("+"), TEXT(" "));
	FixedString.ReplaceInline(TEXT("."), TEXT(" "), ESearchCase::CaseSensitive);

	FixedString.ParseIntoArray(StringArray, TEXT(" "), true);

	if ((StringArray.Num() < 2 || StringArray.Num() == 0))
	{
		return false;
	}

	for (int32 i = 0; i < (StringArray.Num() - 1); ++i)
	{
		OutTime.Append(StringArray[i]);
	}
	return true;
}

void URPGGameInstance::SaveGame(int SlotToUse, bool IsAutoSaving)
{
	bIsAutoSave = IsAutoSaving;
	MC = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(this, 0));
	check(MC);
	UPartySystem* PartyInstance = Cast<UPartySystem>(Party.Get());
	check(PartyInstance);

	if (!CurrentSaveGame)
	{
		URPGSaveGame* SaveGameInstance = Cast<URPGSaveGame>(UGameplayStatics::CreateSaveGameObject(URPGSaveGame::StaticClass()));
		SaveGameInstance->SaveStats.Health = MC->StatsComponent->CurrentHealth;
		SaveGameInstance->SaveStats.Stamina = MC->StatsComponent->CurrentStamina;
		SaveGameInstance->SaveStats.MagicPoints = MC->StatsComponent->CurrentMP;
		SaveGameInstance->SaveStats.XP = MC->StatsComponent->CurrentXP;
		SaveGameInstance->SaveStats.Money = PartyInstance->Money;
		SaveGameInstance->SaveStats.Location = MC->GetActorLocation();
		SaveGameInstance->SaveStats.Rotation = MC->GetActorRotation();
		SaveGameInstance->SaveEquipment.LeftWeaponSlot = MC->CharacterEquipment.LeftWeaponSlot;
		SaveGameInstance->SaveEquipment.RightWeaponSlot = MC->CharacterEquipment.RightWeaponSlot;
		SaveGameInstance->SaveEquipment.LeftArmorSlot = MC->CharacterEquipment.LeftArmorSlot;
		SaveGameInstance->SaveEquipment.RightArmorSlot = MC->CharacterEquipment.RightArmorSlot;
		SaveGameInstance->SaveEquipment.BodySlot = MC->CharacterEquipment.BodySlot;
		SaveGameInstance->SaveEquipment.HandSlot = MC->CharacterEquipment.HandSlot;
		SaveGameInstance->SaveEquipment.LegSlot = MC->CharacterEquipment.LegSlot;
		SaveGameInstance->SaveEquipment.FeetSlot = MC->CharacterEquipment.FeetSlot;
		FString InDate = FDateTime::Now().GetDate().ToString();
		FString InTime = FDateTime::Now().GetTimeOfDay().ToString();
		FString Date;
		FString Time;
		ParseDate(InDate, Date);
		ParseTime(InTime, Time);
		SaveGameInstance->SaveStats.Date = Date;
		SaveGameInstance->SaveStats.Time = Time;
		FString MapName = GetWorld()->GetMapName();
		MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		SaveGameInstance->SaveStats.MapName = MapName;

		for (int32 i = 0; i < MC->Inventory->ItemsArray.Num(); ++i)
		{
			SaveGameInstance->SaveStats.ItemsArray = MC->Inventory->ItemsArray;
		}

		for (int32 i = 0; i < MC->Inventory->WeaponsArray.Num(); ++i)
		{
			SaveGameInstance->SaveStats.WeaponsArray = MC->Inventory->WeaponsArray;
		}

		for (int32 i = 0; i < MC->Inventory->ArmorArray.Num(); ++i)
		{
			SaveGameInstance->SaveStats.ArmorArray = MC->Inventory->ArmorArray;
		}

		CurrentSaveGame = SaveGameInstance;
	}
	else
	{
		CurrentSaveGame->SaveStats.Health = MC->StatsComponent->CurrentHealth;
		CurrentSaveGame->SaveStats.Stamina = MC->StatsComponent->CurrentStamina;
		CurrentSaveGame->SaveStats.MagicPoints = MC->StatsComponent->CurrentMP;
		CurrentSaveGame->SaveStats.XP = MC->StatsComponent->CurrentXP;
		CurrentSaveGame->SaveStats.Money = PartyInstance->Money;
		CurrentSaveGame->SaveStats.Location = MC->GetActorLocation();
		CurrentSaveGame->SaveStats.Rotation = MC->GetActorRotation();
		CurrentSaveGame->SaveEquipment.LeftWeaponSlot = MC->CharacterEquipment.LeftWeaponSlot;
		CurrentSaveGame->SaveEquipment.RightWeaponSlot = MC->CharacterEquipment.RightWeaponSlot;
		CurrentSaveGame->SaveEquipment.LeftArmorSlot = MC->CharacterEquipment.LeftArmorSlot;
		CurrentSaveGame->SaveEquipment.RightArmorSlot = MC->CharacterEquipment.RightArmorSlot;
		CurrentSaveGame->SaveEquipment.BodySlot = MC->CharacterEquipment.BodySlot;
		CurrentSaveGame->SaveEquipment.HandSlot = MC->CharacterEquipment.HandSlot;
		CurrentSaveGame->SaveEquipment.LegSlot = MC->CharacterEquipment.LegSlot;
		CurrentSaveGame->SaveEquipment.FeetSlot = MC->CharacterEquipment.FeetSlot;
		FString Date;
		FString Time;
		ParseDate(FDateTime::Now().GetDate().ToString(), Date);
		ParseTime(FDateTime::Now().GetTimeOfDay().ToString(), Time);
		CurrentSaveGame->SaveStats.Date = Date;
		CurrentSaveGame->SaveStats.Time = Time;
		FString MapName = GetWorld()->GetMapName();
		MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		CurrentSaveGame->SaveStats.MapName = MapName;


		for (int32 i = 0; i < MC->Inventory->ItemsArray.Num(); ++i)
		{
			CurrentSaveGame->SaveStats.ItemsArray = MC->Inventory->ItemsArray;
		}

		for (int32 i = 0; i < MC->Inventory->WeaponsArray.Num(); ++i)
		{
			CurrentSaveGame->SaveStats.WeaponsArray = MC->Inventory->WeaponsArray;
		}

		for (int32 i = 0; i < MC->Inventory->ArmorArray.Num(); ++i)
		{
			CurrentSaveGame->SaveStats.ArmorArray = MC->Inventory->ArmorArray;
		}

	}
		
	switch (SlotToUse)
	{
	case 0:
		SavedGameArray[0] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(0);
		break;
	case 1:
		SavedGameArray[1] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(1);
		break;
	case 2:
		SavedGameArray[2] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(2);
		break;
	case 3:
		SavedGameArray[3] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(3);
		break;
	case 4:
		SavedGameArray[4] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(4);
		break;
	case 5:
		SavedGameArray[5] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(5);
		break;
	case 6:
		SavedGameArray[6] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(6);
		break;
	case 7:
		SavedGameArray[7] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(7);
		break;
	case 8:
		SavedGameArray[8] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(8);
		break;
	case 9:
		SavedGameArray[9] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(9);
		break;
	case 10:
		SavedGameArray[10] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(10);
		break;
	case 11:
		SavedGameArray[11] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(11);
		break;
	case 12:
		SavedGameArray[12] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(12);
		break;
	case 13:
		SavedGameArray[13] = CurrentSaveGame;
		CurrentSaveGame->CreateSlot(13);
	default:
		break;
	}
		
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, CurrentSaveGame->SlotName, CurrentSaveGame->UserIndex);
}

void URPGGameInstance::LoadGame(FString SaveSlotName)
{
	MC = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(this, 0));
	check(MC);
	UPartySystem* PartyInstance = Cast<UPartySystem>(Party.Get());
	check(PartyInstance);

	URPGSaveGame* LoadGameInstance = Cast<URPGSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	CurrentSaveGame = LoadGameInstance;

	if (LoadGameInstance)
	{
		MC->StatsComponent->CurrentHealth = LoadGameInstance->SaveStats.Health;
		MC->StatsComponent->CurrentMP = LoadGameInstance->SaveStats.MagicPoints;
		MC->StatsComponent->CurrentStamina = LoadGameInstance->SaveStats.Stamina;
		PartyInstance->Money = LoadGameInstance->SaveStats.Money;
		MC->CharacterEquipment.LeftWeaponSlot = LoadGameInstance->SaveEquipment.LeftWeaponSlot;
		MC->CharacterEquipment.LeftArmorSlot = LoadGameInstance->SaveEquipment.LeftArmorSlot;
		MC->CharacterEquipment.RightArmorSlot = LoadGameInstance->SaveEquipment.RightArmorSlot;
		MC->CharacterEquipment.RightWeaponSlot = LoadGameInstance->SaveEquipment.RightWeaponSlot;
		MC->CharacterEquipment.BodySlot = LoadGameInstance->SaveEquipment.BodySlot;
		MC->CharacterEquipment.HandSlot = LoadGameInstance->SaveEquipment.HandSlot;
		MC->CharacterEquipment.LegSlot = LoadGameInstance->SaveEquipment.LegSlot;
		MC->CharacterEquipment.FeetSlot = LoadGameInstance->SaveEquipment.FeetSlot;

		if (MC->Inventory)
		{
			if (MC->CharacterEquipment.LeftWeaponSlot)
			{
				AWeaponBase* WeaponToEquip = MC->CharacterEquipment.LeftWeaponSlot;
				MC->Inventory->EquipHandSlot(WeaponToEquip, nullptr, true);
			}
			if (MC->CharacterEquipment.LeftArmorSlot)
			{
				AArmorBase* ShieldToEquip = MC->CharacterEquipment.LeftArmorSlot;
				MC->Inventory->EquipHandSlot(nullptr, ShieldToEquip, true);
			}
			if (MC->CharacterEquipment.RightWeaponSlot)
			{
				AWeaponBase* WeaponToEquip = MC->CharacterEquipment.RightWeaponSlot;
				MC->Inventory->EquipHandSlot(WeaponToEquip, nullptr, false);
			}
			if (MC->CharacterEquipment.RightArmorSlot)
			{
				AArmorBase* ShieldToEquip = MC->CharacterEquipment.RightArmorSlot;
				MC->Inventory->EquipHandSlot(nullptr, ShieldToEquip, false);
			}
			if (MC->CharacterEquipment.BodySlot)
			{
				AArmorBase* Armor = MC->CharacterEquipment.BodySlot;
				MC->Inventory->EquipArmorSlot(Armor);
			}
			if (MC->CharacterEquipment.HandSlot)
			{
				AArmorBase* Armor = MC->CharacterEquipment.HandSlot;
				MC->Inventory->EquipArmorSlot(Armor);
			}
			if (MC->CharacterEquipment.LegSlot)
			{
				AArmorBase* Armor = MC->CharacterEquipment.LegSlot;
				MC->Inventory->EquipArmorSlot(Armor);
			}
			if (MC->CharacterEquipment.FeetSlot)
			{
				AArmorBase* Armor = MC->CharacterEquipment.FeetSlot;
				MC->Inventory->EquipArmorSlot(Armor);
			}
		}

		for (int32 i = 0; i < LoadGameInstance->SaveStats.ItemsArray.Num(); ++i)
		{
			MC->Inventory->ItemsArray = LoadGameInstance->SaveStats.ItemsArray;
		}

		for (int32 i = 0; i < LoadGameInstance->SaveStats.WeaponsArray.Num(); ++i)
		{
			MC->Inventory->WeaponsArray = LoadGameInstance->SaveStats.WeaponsArray;
		}

		for (int32 i = 0; i < LoadGameInstance->SaveStats.ArmorArray.Num(); ++i)
		{
			MC->Inventory->ArmorArray = LoadGameInstance->SaveStats.ArmorArray;
		}

		if (!MC->IsDead())
		{
			MC->SetMovementStatus(MC->MovementSpeed);
			MC->GetMesh()->bPauseAnims = false;
			MC->GetMesh()->bNoSkeletonUpdate = false;
		}

		/**
		if (LoadGameInstance->Enemies.Num() != 0)
		{
			for (int32 i = 0; i < LoadGameInstance->Enemies.Num(); ++i)
			{
				GetWorld()->SpawnActor<AEnemyBase>(LoadGameInstance->Enemies[i]);
			}
		}
		*/
		if (LoadGameInstance->SaveStats.MapName != TEXT(""))
		{
			FName MapName(*LoadGameInstance->SaveStats.MapName);
			SwitchLevel(MapName);
		}
		
	}
}

void URPGGameInstance::LoadGameNoSwitch(bool bSetPosition, FString SaveSlotName)
{
	MC = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(this, 0));
	check(MC);
	UPartySystem* PartyInstance = Cast<UPartySystem>(Party.Get());
	check(PartyInstance);

	URPGSaveGame* LoadGameInstance = Cast<URPGSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	CurrentSaveGame = LoadGameInstance;

	if (LoadGameInstance)
	{
		MC->StatsComponent->Health = LoadGameInstance->SaveStats.Health;
		MC->StatsComponent->MagicPoints = LoadGameInstance->SaveStats.MagicPoints;
		MC->StatsComponent->Stamina = LoadGameInstance->SaveStats.Stamina;
		PartyInstance->Money = LoadGameInstance->SaveStats.Money;
		MC->CharacterEquipment.LeftWeaponSlot = LoadGameInstance->SaveEquipment.LeftWeaponSlot;
		MC->CharacterEquipment.LeftArmorSlot = LoadGameInstance->SaveEquipment.LeftArmorSlot;
		MC->CharacterEquipment.RightArmorSlot = LoadGameInstance->SaveEquipment.RightArmorSlot;
		MC->CharacterEquipment.RightWeaponSlot = LoadGameInstance->SaveEquipment.RightWeaponSlot;
		MC->CharacterEquipment.BodySlot = LoadGameInstance->SaveEquipment.BodySlot;
		MC->CharacterEquipment.HandSlot = LoadGameInstance->SaveEquipment.HandSlot;
		MC->CharacterEquipment.LegSlot = LoadGameInstance->SaveEquipment.LegSlot;
		MC->CharacterEquipment.FeetSlot = LoadGameInstance->SaveEquipment.FeetSlot;

		if (MC->Inventory)
		{
			if (MC->CharacterEquipment.LeftWeaponSlot)
			{
				AWeaponBase* WeaponToEquip = MC->CharacterEquipment.LeftWeaponSlot;
				MC->Inventory->EquipHandSlot(WeaponToEquip, nullptr, true);
			}
			if (MC->CharacterEquipment.LeftArmorSlot)
			{
				AArmorBase* ShieldToEquip = MC->CharacterEquipment.LeftArmorSlot;
				MC->Inventory->EquipHandSlot(nullptr, ShieldToEquip, true);
			}
			if (MC->CharacterEquipment.RightWeaponSlot)
			{
				AWeaponBase* WeaponToEquip = MC->CharacterEquipment.RightWeaponSlot;
				MC->Inventory->EquipHandSlot(WeaponToEquip, nullptr, false);
			}
			if (MC->CharacterEquipment.RightArmorSlot)
			{
				AArmorBase* ShieldToEquip = MC->CharacterEquipment.RightArmorSlot;
				MC->Inventory->EquipHandSlot(nullptr, ShieldToEquip, false);
			}
			if (MC->CharacterEquipment.BodySlot)
			{
				AArmorBase* Armor = MC->CharacterEquipment.BodySlot;
				MC->Inventory->EquipArmorSlot(Armor);
			}
			if (MC->CharacterEquipment.HandSlot)
			{
				AArmorBase* Armor = MC->CharacterEquipment.HandSlot;
				MC->Inventory->EquipArmorSlot(Armor);
			}
			if (MC->CharacterEquipment.LegSlot)
			{
				AArmorBase* Armor = MC->CharacterEquipment.LegSlot;
				MC->Inventory->EquipArmorSlot(Armor);
			}
			if (MC->CharacterEquipment.FeetSlot)
			{
				AArmorBase* Armor = MC->CharacterEquipment.FeetSlot;
				MC->Inventory->EquipArmorSlot(Armor);
			}
		}

		for (int32 i = 0; i < LoadGameInstance->SaveStats.ItemsArray.Num(); ++i)
		{
			MC->Inventory->ItemsArray = LoadGameInstance->SaveStats.ItemsArray;
		}

		for (int32 i = 0; i < LoadGameInstance->SaveStats.WeaponsArray.Num(); ++i)
		{
			MC->Inventory->WeaponsArray = LoadGameInstance->SaveStats.WeaponsArray;
		}

		for (int32 i = 0; i < LoadGameInstance->SaveStats.ArmorArray.Num(); ++i)
		{
			MC->Inventory->ArmorArray = LoadGameInstance->SaveStats.ArmorArray;
		}

		if (!MC->IsDead())
		{
			MC->SetMovementStatus(MC->MovementSpeed);
			MC->GetMesh()->bPauseAnims = false;
			MC->GetMesh()->bNoSkeletonUpdate = false;
		}

		if (bSetPosition)
		{
			MC->SetActorLocation(LoadGameInstance->SaveStats.Location);
			MC->SetActorRotation(LoadGameInstance->SaveStats.Rotation);
		}

		/**
		if (LoadGameInstance->Enemies.Num() != 0)
		{
			for (int32 i = 0; i < LoadGameInstance->Enemies.Num(); ++i)
			{
				GetWorld()->SpawnActor<AEnemyBase>(LoadGameInstance->Enemies[i]);
			}
		}
		*/
	}
}

void URPGGameInstance::SwitchLevel(FName MapName)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FString CurrentLevel = World->GetMapName();

		FName CurrentLevelName(*CurrentLevel);
		if (CurrentLevelName != MapName)
		{
			UGameplayStatics::OpenLevel(World, MapName);
		}
	}
}

