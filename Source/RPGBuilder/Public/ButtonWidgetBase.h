// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidgetBase.h"
#include "ButtonWidgetBase.generated.h"

class UTextBlock;
class UButton;
class ARPGPlayerController;
class URPGGameInstance;
class USoundCue;

/**
 * 
 */
UCLASS()
class RPGBUILDER_API UButtonWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	FORCEINLINE ARPGPlayerController* GetPlayerController() { return PC; }

	FORCEINLINE URPGGameInstance* GetGameInstance() { return GameInstance; }

	FORCEINLINE void SetPlayerController(ARPGPlayerController* Controller) { PC = Controller; }

	FORCEINLINE void SetGameInstance(URPGGameInstance* GI) { GameInstance = GI; }

	UFUNCTION()
		void OnHovered();
	UFUNCTION()
		void OnClicked();
	UFUNCTION()
		void SetColorOnFocus(UButton* Button);


public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Text = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* MenuButton = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		UWidgetAnimation* WidgetAnimation = nullptr;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		USoundCue* OnHoverSound = nullptr;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		USoundCue* OnClickSound = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enums", meta = (ToolTip = "***REQUIRED*** Use this to set Menu Type "))
		EMenuType MenuType = EMenuType::EMS_MAX;

	bool bPlayAnimForward = false;
	bool bPlayAnimBackward = false;
	bool bInitialAnimPlay = true;

	ARPGPlayerController* PC = nullptr;

	URPGGameInstance* GameInstance = nullptr;

	
};
