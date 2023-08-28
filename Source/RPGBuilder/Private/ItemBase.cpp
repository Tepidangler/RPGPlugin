#include "ItemBase.h"
#include "CharacterBase.h"
#include "InventoryComponent.h"

UItemBase::UItemBase()
{
	ItemName = "DefaultName";
	ItemDescription = "Description";
	Defense = 0;
	Attack = 0;
	Health = 0;
	MagicPoints = 0;
	Intelligence = 0;
	Agility = 0;
	Stamina = 0;
	Strength = 0;

}

bool UItemBase::AddBuff(ACharacterBase* MC)
{
	if (MC)
	{
		switch (ItemBuffType)
		{
		case EItemBuffType::EIBT_HealthBuff:
			MC->AddItemBuff(Health, ItemBuffType);
			return true;

		case EItemBuffType::EIBT_MagicPointsBuff:
			MC->AddItemBuff(MagicPoints, ItemBuffType);
			return true;

		case EItemBuffType::EIBT_StrengthBuff:
			MC->AddItemBuff(Strength, ItemBuffType);
			return true;

		case EItemBuffType::EIBT_DefenseBuff:
			MC->AddItemBuff(Defense, ItemBuffType);
			return true;

		case EItemBuffType::EIBT_AgilityBuff:
			MC->AddItemBuff(Agility, ItemBuffType);
			return true;

		case EItemBuffType::EIBT_IntelligenceBuff:
			MC->AddItemBuff(Intelligence, ItemBuffType);
			return true;

		case EItemBuffType::EIBT_StaminaBuff:
			MC->AddItemBuff(Stamina, ItemBuffType);
			return true;

		default:
			break;
		}

	}
	return false;
}

bool UItemBase::AddDebuff(ACharacterBase* MC)
{
	if (MC)
	{
		switch (ItemDebuffType)
		{
		case EItemDebuffType::EIDT_HealthDebuff:
			MC->AddItemDebuff(Health, ItemDebuffType);
			return true;

		case EItemDebuffType::EIDT_MagicPointsDebuff:
			MC->AddItemDebuff(MagicPoints, ItemDebuffType);
			return true;

		case EItemDebuffType::EIDT_StrengthDebuff:
			MC->AddItemDebuff(Strength, ItemDebuffType);
			return true;

		case EItemDebuffType::EIDT_DefenseDebuff:
			MC->AddItemDebuff(Defense, ItemDebuffType);
			return true;

		case EItemDebuffType::EIDT_AgilityDebuff:
			MC->AddItemDebuff(Agility, ItemDebuffType);
			return true;

		case EItemDebuffType::EIDT_IntelligenceDebuff:
			MC->AddItemDebuff(Intelligence, ItemDebuffType);
			return true;

		case EItemDebuffType::EIDT_StaminaDebuff:
			MC->AddItemDebuff(Stamina, ItemDebuffType);
			return true;

		default:
			break;
		}

	}
	return false;
}

bool UItemBase::RemoveBuff(ACharacterBase* MC)
{
	if (MC)
	{
		switch (ItemDebuffType)
		{
		case EItemDebuffType::EIDT_HealthDebuff:
			MC->AddItemDebuff(Health, ItemDebuffType);
			return true;

		case EItemDebuffType::EIDT_MagicPointsDebuff:
			MC->AddItemDebuff(MagicPoints, ItemDebuffType);
			return true;

		case EItemDebuffType::EIDT_StrengthDebuff:
			MC->AddItemDebuff(Strength, ItemDebuffType);
			return true;

		case EItemDebuffType::EIDT_DefenseDebuff:
			MC->AddItemDebuff(Defense, ItemDebuffType);
			return true;

		case EItemDebuffType::EIDT_AgilityDebuff:
			MC->AddItemDebuff(Agility, ItemDebuffType);
			return true;

		case EItemDebuffType::EIDT_IntelligenceDebuff:
			MC->AddItemDebuff(Intelligence, ItemDebuffType);
			return true;

		case EItemDebuffType::EIDT_StaminaDebuff:
			MC->AddItemDebuff(Stamina, ItemDebuffType);
			return true;

		default:
			break;
		}

	}
	return false;
}

bool UItemBase::AddToInventory(ACharacterBase* MC)
{
	if (MC->Inventory->AddItem(this))
	{
		return true;
	}
	return false;

}