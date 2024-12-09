// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PartySystem.h"
#include "Components/Button.h"
#include "RPGGameInstance.generated.h"

/**
 * 
 */

class UPartySystem;
class URPGSaveGame;
class ARPGPlayerController;

UCLASS()
class RPGBUILDER_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	URPGGameInstance();

	UFUNCTION(BlueprintCallable)
		void SaveGame(int SlotToUse, bool IsAutoSaving);
	UFUNCTION(BlueprintCallable)
		void LoadGame(FString SaveSlotName);
	UFUNCTION(BlueprintCallable)
		void LoadGameNoSwitch(bool bSetPosition, FString SaveSlotName);

		void SwitchLevel(FName MapName);



protected:
	virtual void Init() override;

	void BeginPlay();

	virtual void PostInitProperties() override;

	bool ParseDate(const FString& DateTimeString, FString& OutDate);

	bool ParseTime(const FString& DateTimeString, FString& OutTime);

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Party System")
	TSubclassOf<UPartySystem> Party;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Game")
	TArray<URPGSaveGame*> SavedGameArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	TArray<UButton*> MenuButtonArray;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save Game", meta = (ToolTip = "Max Number Of Available Save Slots"))
	int32 MaxSaveSlots = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Game")
	URPGSaveGame* CurrentSaveGame = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Save Game")
	ACharacterBase* MC = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Save Game")
	ARPGPlayerController* PC = nullptr;
	bool bIsAutoSave = false;
};
