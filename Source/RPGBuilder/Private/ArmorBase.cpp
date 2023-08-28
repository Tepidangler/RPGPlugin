#include "ArmorBase.h"
#include "CharacterBase.h"
#include "InventoryComponent.h"
#include "StatsComponent.h"

// Sets default values
AArmorBase::AArmorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Name = "DefaultName";
	ArmorDescription = "Description";
	Defense = 0;
	Health = 0;
	MagicPoints = 0;
	Intelligence = 0;
}

// Called when the game starts or when spawned
void AArmorBase::BeginPlay()
{
	Super::BeginPlay();

}

void AArmorBase::AddBuff(ACharacterBase* MC)
{
	switch (BuffType)
	{
	case EBuffType::EBT_Health:
		MC->StatsComponent->Health += Health;
		break;
	case EBuffType::EBT_Defense:
		MC->StatsComponent->Defense += Defense;
		break;
	case EBuffType::EBT_MagicPoints:
		MC->StatsComponent->MagicPoints += MagicPoints;
		break;
	case EBuffType::EBT_Intelligence:
		MC->StatsComponent->Intelligence += Intelligence;
		break;
	}
}

void AArmorBase::RemoveBuff(ACharacterBase* MC)
{
	switch (BuffType)
	{
	case EBuffType::EBT_Health:
		MC->StatsComponent->Health -= Health;
		break;
	case EBuffType::EBT_Defense:
		MC->StatsComponent->Defense -= Defense;
		break;
	case EBuffType::EBT_MagicPoints:
		MC->StatsComponent->MagicPoints -= MagicPoints;
		break;
	case EBuffType::EBT_Intelligence:
		MC->StatsComponent->Intelligence -= Intelligence;
		break;
	}
}

bool AArmorBase::IsArmorTypeSet()
{
	if (ArmorType != EArmorType::EAT_DEFAULTMAX)
	{
		return true;
	}

	return false;
}

void AArmorBase::AddToInventory(ACharacterBase* MC)
{
	MC->Inventory->AddArmor(this);

}
