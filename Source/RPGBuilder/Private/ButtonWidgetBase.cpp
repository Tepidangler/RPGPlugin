// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonWidgetBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MenuWidgetBase.h"
#include "RPGPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "RPGGameInstance.h"
#include "ItemBase.h"
#include "WeaponBase.h"
#include "ArmorBase.h"
#include "AbilityBase.h"
#include "MagicBase.h"
#include "CharacterBase.h"
#include "InventoryComponent.h"

void UButtonWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	SetPlayerController(Cast<ARPGPlayerController>(UGameplayStatics::GetPlayerController(this, 0)));
	Text->SetText(FText::FromString("Text"));
	MenuButton->OnHovered.AddDynamic(this, &UButtonWidgetBase::OnHovered);
	MenuButton->OnClicked.AddDynamic(this, &UButtonWidgetBase::OnClicked);
	SetGameInstance(Cast<URPGGameInstance>(UGameplayStatics::GetGameInstance(this)));
	GameInstance->MenuButtonArray.Add(MenuButton);

	SetUserFocus(PC);
}

void UButtonWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bInitialAnimPlay)
	{
		bPlayAnimForward = true;
		bInitialAnimPlay = false;
	}
	SetColorOnFocus(MenuButton);
}

void UButtonWidgetBase::OnHovered()
{
	SetUserFocus(PC);
	bPlayAnimForward = true;
}

void UButtonWidgetBase::OnClicked()
{
	check(PC);
	check(OnClickSound);
	UGameplayStatics::PlaySound2D(this, OnClickSound);
}

void UButtonWidgetBase::SetColorOnFocus(UButton* Button)
{
	check(PC);
	check(WidgetAnimation);
	if (MenuButton->HasUserFocus(PC))
	{

		if (bPlayAnimForward)
		{
			bPlayAnimForward = false;
			PlayAnimation(WidgetAnimation, 0.f, 1.f, EUMGSequencePlayMode::Forward, 1.f, false);
			bPlayAnimBackward = true;
			check(OnHoverSound);
			UGameplayStatics::PlaySound2D(this, OnHoverSound);
		}

	}
	else
	{
		if (bPlayAnimBackward)
		{
			//check(WidgetAnimation);
			bPlayAnimBackward = false;
			PlayAnimation(WidgetAnimation, GetAnimationCurrentTime(WidgetAnimation), 1.f, EUMGSequencePlayMode::Reverse, 1.f, false);
			bPlayAnimForward = true;
		}
	}
}
