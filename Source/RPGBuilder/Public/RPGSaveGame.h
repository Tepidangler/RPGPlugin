// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RPGSaveGame.generated.h"

/**
 * 
 */
class UInventoryComponent;
class AWeaponBase;
class AArmorBase;
class UItemBase;

USTRUCT(BlueprintType)
struct FSaveStats
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveGameData")
		FString Date;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveGameData")
		FString Time;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		float Health;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		float MagicPoints;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		float Stamina;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		float XP;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		int32 Money;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		FVector Location;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		FRotator Rotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveGameData")
		FString MapName;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		FString WeaponName;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		TArray<UItemBase*> ItemsArray;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		TArray<AWeaponBase*> WeaponsArray;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		TArray<AArmorBase*> ArmorArray;
};

USTRUCT(BlueprintType)
struct FSaveEquipment
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		AWeaponBase* LeftWeaponSlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		AWeaponBase* RightWeaponSlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		AArmorBase* LeftArmorSlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		AArmorBase* RightArmorSlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		AArmorBase* BodySlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		AArmorBase* HandSlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		AArmorBase* LegSlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
		AArmorBase* FeetSlot = nullptr;


};

UCLASS()
class RPGBUILDER_API URPGSaveGame : public USaveGame
{
	GENERATED_BODY()


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		FString SlotName;
	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		FSaveStats SaveStats;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		FSaveEquipment SaveEquipment;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		int SlotNumber;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
	//TArray<AEnemyBase*> Enemies;

public:

	//Functions
	URPGSaveGame();

	void CreateSlot(int SaveSlotNumber);

	void CreateEmptySlot(int SaveSlotNumber);

	FString CreateSaveSlotName(int SaveSlotNumber);

	FString GetSlotName();

};


