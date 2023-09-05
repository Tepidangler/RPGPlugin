#include "ArmorBase.h"
#include "CharacterBase.h"
#include "InventoryComponent.h"

// Sets default values
AArmorBase::AArmorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Name = "DefaultName";
	ArmorDescription = "Description";
	Defense = 0;
}

// Called when the game starts or when spawned
void AArmorBase::BeginPlay()
{
	Super::BeginPlay();

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
