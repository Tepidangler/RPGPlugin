// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidgetBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "RPGPlayerController.h"
#include "RPGGameInstance.h"
#include "Components/WrapBox.h"
#include "CharacterBase.h"
#include "InventoryComponent.h"
#include "ButtonWidgetBase.h"

void UMenuWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	OnNativeVisibilityChanged.AddUObject(this, &UMenuWidgetBase::VisbilityChanged);
	ACharacterBase* MC = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SetPlayerController(Cast<ARPGPlayerController>(UGameplayStatics::GetPlayerController(this, 0)));

	SetGameInstance(Cast<URPGGameInstance>(UGameplayStatics::GetGameInstance(this)));
	check(MC);
	if (ContentNames.Num() == 0)
	{
		Rows = MC->Inventory->ItemsArray.Num();
	}
	else
	{
		Rows = ContentNames.Num();
	}

	check(SlotWidgetClass);

	if (SlotWrapBox)
	{
		SlotWrapBox->ClearChildren();
		//UItemSlotPanelWidget::StaticSlotScrollBox->ClearChildren();

		for (int32 y = 0; y < Rows; ++y)
		{
			if (MC->Inventory->ItemsArray[y])
			{
				//UItemSlotPanelWidget::ItemNames.AddUnique(MC->Inventory->ItemsArray[y]->ItemName);

				SlotWrapBox->AddChild(CreateWidget(GetWorld(), SlotWidgetClass));

			}

		}
	}

	if (!bIsFocusSet && SlotWrapBox->GetChildAt(0))
	{
		SlotWrapBox->GetChildAt(0)->SetUserFocus(PC);
		bIsFocusSet = true;
	}

	ButtonLastFocused = GameInstance->MenuButtonArray[0];

}

void UMenuWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SlotWrapBox->HasUserFocusedDescendants(PC))
	{

		for (int32 i = 0; i < GameInstance->MenuButtonArray.Num(); ++i)
		{
			if (GameInstance->MenuButtonArray[i]->HasUserFocus(PC))
			{
				ButtonLastFocused = GameInstance->MenuButtonArray[i];
			}
		}
	}
	else
	{
		if (PC->WasInputKeyJustPressed(EKeys::AnyKey) && ButtonLastFocused)
		{
			ButtonLastFocused->SetUserFocus(PC);
		}
	}

}

void UMenuWidgetBase::RefreshWidgets()
{
	RebuildWidget();
	OnWidgetRebuilt();
}

void UMenuWidgetBase::VisbilityChanged(ESlateVisibility InVisibility)
{
	RefreshWidgets();
}

ARPGPlayerController* UMenuWidgetBase::GetPlayerController()
{
	if (PC)
	{
		return PC;
	}
	else
	{
		return Cast<ARPGPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	}
	return nullptr; // If we've gotten here that means I did something wrong
}

URPGGameInstance* UMenuWidgetBase::GetGameInstance()
{
	if (GameInstance)
	{
		return GameInstance;
	}
	else
	{
		return Cast<URPGGameInstance>(UGameplayStatics::GetGameInstance(this));
	}
	return nullptr; // If we've gotten here that means I did something wrong
}
