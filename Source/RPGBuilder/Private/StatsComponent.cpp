// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "ItemBase.h"
#include "MagicBase.h"

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

void UStatsComponent::AddMagicBuff(float Value, EMagicBuffType Type)
{
	float NewValue;
	switch (Type)
	{
	case EMagicBuffType::EMBT_HealthBuff:
		NewValue = Health.GetValue() * Value;
		Health.SetValue(NewValue);
		break;
	case EMagicBuffType::EMBT_MagicPointsBuff:
		NewValue = MagicPoints.GetValue() * Value;
		MagicPoints.SetValue(NewValue);
		break;
	case EMagicBuffType::EMBT_StrengthBuff:
		NewValue = Strength.GetValue() * Value;
		Strength.SetValue(NewValue);
		break;
	case EMagicBuffType::EMBT_DefenseBuff:
		NewValue = Defense.GetValue() * Value;
		Defense.SetValue(NewValue);
		break;
	case EMagicBuffType::EMBT_AgilityBuff:
		NewValue = Agility.GetValue() * Value;
		Agility.SetValue(NewValue);
		break;
	case EMagicBuffType::EMBT_IntelligenceBuff:
		NewValue = Intelligence.GetValue() * Value;
		Intelligence.SetValue(NewValue);
		break;
	case EMagicBuffType::EMBT_StaminaBuff:
		NewValue = Stamina.GetValue() * Value;
		Stamina.SetValue(NewValue);
		break;
	default:
		break;
	}
}

void UStatsComponent::AddMagicDebuff(float Value, EMagicDebuffType Type)
{
	float NewValue;
	switch (Type)
	{
	case EMagicDebuffType::EMDT_HealthBuff:
		NewValue = Health.GetValue() * Value;
		Health.SetValue(NewValue);
		break;
	case EMagicDebuffType::EMDT_MagicPointsBuff:
		NewValue = MagicPoints.GetValue() * Value;
		MagicPoints.SetValue(NewValue);
		break;
	case EMagicDebuffType::EMDT_StrengthBuff:
		NewValue = Strength.GetValue() * Value;
		Strength.SetValue(NewValue);
		break;
	case EMagicDebuffType::EMDT_DefenseBuff:
		NewValue = Defense.GetValue() * Value;
		Defense.SetValue(NewValue);
		break;
	case EMagicDebuffType::EMDT_AgilityBuff:
		NewValue = Agility.GetValue() * Value;
		Agility.SetValue(NewValue);
		break;
	case EMagicDebuffType::EMDT_IntelligenceBuff:
		NewValue = Intelligence.GetValue() * Value;
		Intelligence.SetValue(NewValue);
		break;
	case EMagicDebuffType::EMDT_StaminaBuff:
		NewValue = Stamina.GetValue() * Value;
		Stamina.SetValue(NewValue);
		break;
	default:
		break;
	}
}

void UStatsComponent::AddItemBuff(float Value, EItemBuffType Type)
{
	switch (Type)
	{
	case EItemBuffType::EIBT_HealthBuff:
		Health.SetValue(Health.GetValue() + Value);

	case EItemBuffType::EIBT_MagicPointsBuff:
		MagicPoints.SetValue(MagicPoints.GetValue() + Value);

	case EItemBuffType::EIBT_StrengthBuff:
		Strength.SetValue(Strength.GetValue() + Value);

	case EItemBuffType::EIBT_DefenseBuff:
		Defense.SetValue(Defense.GetValue() + Value);

	case EItemBuffType::EIBT_AgilityBuff:
		Agility.SetValue(Agility.GetValue() + Value);

	case EItemBuffType::EIBT_IntelligenceBuff:
		Intelligence.SetValue(Intelligence.GetValue() + Value);

	case EItemBuffType::EIBT_StaminaBuff:
		Stamina.SetValue(Stamina.GetValue() + Value);

	default:
		break;
	}
}
void UStatsComponent::AddItemDebuff(float Value, EItemDebuffType Type)
{

	switch (Type)
	{
	case EItemDebuffType::EIDT_HealthDebuff:
		Health.SetValue(Health.GetValue() + Value);

	case EItemDebuffType::EIDT_MagicPointsDebuff:
		MagicPoints.SetValue(MagicPoints.GetValue() + Value);

	case EItemDebuffType::EIDT_StrengthDebuff:
		Strength.SetValue(Strength.GetValue() + Value);

	case EItemDebuffType::EIDT_DefenseDebuff:
		Defense.SetValue(Defense.GetValue() + Value);

	case EItemDebuffType::EIDT_AgilityDebuff:
		Agility.SetValue(Agility.GetValue() + Value);

	case EItemDebuffType::EIDT_IntelligenceDebuff:
		Intelligence.SetValue(Intelligence.GetValue() + Value);

	case EItemDebuffType::EIDT_StaminaDebuff:
		Stamina.SetValue(Stamina.GetValue() + Value);
	default:
		break;
	}

}