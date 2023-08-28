// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "ItemBase.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	CurrentHealth = Health.GetValueAtLevel(Level);
	CurrentMP = MagicPoints.GetValueAtLevel(Level);
	CurrentStamina = Stamina.GetValueAtLevel(Level);
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = Health.GetValueAtLevel(Level);
	CurrentMP = MagicPoints.GetValueAtLevel(Level);
	CurrentStamina = Stamina.GetValueAtLevel(Level);
	
}


/**
// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/

void UStatsComponent::AddXP(float XP)
{
	if (XP + CurrentXP >= XPToNextLevel.GetValueAtLevel(Level))
	{
		++Level;
	}
	else
	{
		CurrentXP += XP;
	}
}

void UStatsComponent::AddMagicBuff(float Value/*, enum type*/)
{

}

void UStatsComponent::AddMagicDebuff(float Value/*, enum type*/)
{

}

void UStatsComponent::AddItemBuff(float Value, EItemBuffType Type)
{
	switch (Type)
	{
	case EItemBuffType::EIBT_HealthBuff:
		Health.SetValue(Health.GetValueAtLevel(Level) +Value);

	case EItemBuffType::EIBT_MagicPointsBuff:
		MagicPoints.SetValue(MagicPoints.GetValueAtLevel(Level) + Value);

	case EItemBuffType::EIBT_StrengthBuff:
		Strength.SetValue(Strength.GetValueAtLevel(Level) + Value);

	case EItemBuffType::EIBT_DefenseBuff:
		Defense.SetValue(Defense.GetValueAtLevel(Level) + Value);

	case EItemBuffType::EIBT_AgilityBuff:
		Agility.SetValue(Agility.GetValueAtLevel(Level) + Value);

	case EItemBuffType::EIBT_IntelligenceBuff:
		Intelligence.SetValue(Intelligence.GetValueAtLevel(Level) + Value);

	case EItemBuffType::EIBT_StaminaBuff:
		Stamina.SetValue(Stamina.GetValueAtLevel(Level) + Value);

	default:
		break;
	}
}
void UStatsComponent::AddItemDebuff(float Value, EItemDebuffType Type)
{

	switch (Type)
	{
	case EItemDebuffType::EIDT_HealthDebuff:
		Health.SetValue(Health.GetValueAtLevel(Level) + Value);

	case EItemDebuffType::EIDT_MagicPointsDebuff:
		MagicPoints.SetValue(MagicPoints.GetValueAtLevel(Level) + Value);

	case EItemDebuffType::EIDT_StrengthDebuff:
		Strength.SetValue(Strength.GetValueAtLevel(Level) + Value);

	case EItemDebuffType::EIDT_DefenseDebuff:
		Defense.SetValue(Defense.GetValueAtLevel(Level) + Value);

	case EItemDebuffType::EIDT_AgilityDebuff:
		Agility.SetValue(Agility.GetValueAtLevel(Level) + Value);

	case EItemDebuffType::EIDT_IntelligenceDebuff:
		Intelligence.SetValue(Intelligence.GetValueAtLevel(Level) + Value);

	case EItemDebuffType::EIDT_StaminaDebuff:
		Stamina.SetValue(Stamina.GetValueAtLevel(Level) + Value);
	default:
		break;
	}

}