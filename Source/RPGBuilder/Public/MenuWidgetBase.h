// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidgetBase.generated.h"


UENUM(BlueprintType)
enum class EMenuType : uint8
{
	EMT_MainMenu UMETA(DisplayName = "Main Menu"),
	EMS_ItemMenu UMETA(DisplayName = "Item Menu"),
	EMS_AbilityMenu UMETA(DisplayName = "Ability Menu"),
	EMS_MagicMenu UMETA(DisplayName = "Magic Menu"),
	EMS_EquipmentMenu UMETA(DisplayName = "Equipment Menu"),
	EMS_StatusMenu UMETA(DisplayName = "Status Menu"),
	EMS_PartyMenu UMETA(DisplayName = "Party Menu"),
	EMS_ConfigMenu UMETA(DisplayName = "Config Menu"),
	EMS_SaveMenu UMETA(DisplayName = "Save Menu"),
	EMS_LoadMenu UMETA(DisplayName = "Load Menu"),
	EMS_OptionsMenu UMETA(DisplayName = "Options Menu"),

	EMS_MAX UMETA(DisplayName = "Default")

};

UENUM(BlueprintType)
enum class EWidgetDisplayType : uint8
{
	EWDT_Panel UMETA(DisplayName = "Panel Display", ToolTip = "Displays child widgets using panels"),
	EWDT_Button UMETA(DisplayName = "Button Display", ToolTip = "Displays child widgets using buttons"),

	EWDT_MAX UMETA(DisplayName = "Default")
};

/**
 * 
 */
class UTextBlock;
class UButton;
class ARPGPlayerController;
class URPGGameInstance;
class UButtonWidgetBase;
class UWrapBox;

UCLASS()
class RPGBUILDER_API UMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public: // Functions
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void RefreshWidgets();

	UFUNCTION()
		void VisbilityChanged(ESlateVisibility InVisibility);

	ARPGPlayerController* GetPlayerController();

	URPGGameInstance* GetGameInstance();

	FORCEINLINE void SetPlayerController(ARPGPlayerController* Controller) { PC = Controller; }

	FORCEINLINE void SetGameInstance(URPGGameInstance* GI) { GameInstance = GI; }

public: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enums", meta = (ToolTip = "***REQUIRED*** Use this to set Menu Type "))
	EMenuType MenuType;

	UPROPERTY(EditAnywhere, Category = "Slot Panel")
	TSubclassOf<UButtonWidgetBase> SlotWidgetClass = nullptr;
	UPROPERTY(EditAnywhere, Category = "Slot Panel")
	int32 Rows = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Slot Panel", meta = (BindWidget))
	UWrapBox* SlotWrapBox;

protected:

	UPROPERTY()
	ARPGPlayerController* PC = nullptr;

	UPROPERTY()
	URPGGameInstance* GameInstance = nullptr;

	TArray<FName> ContentNames;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UButton* ButtonLastFocused = nullptr;
	UPROPERTY()
		bool bIsFocusSet = false;


	
};

