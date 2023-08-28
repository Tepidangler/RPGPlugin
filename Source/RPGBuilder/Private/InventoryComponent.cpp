#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{

}

bool UInventoryComponent::AddItem(UItemBase* Item)
{
    return false;
}

void UInventoryComponent::RemoveItem(UItemBase* Item)
{
}

void UInventoryComponent::AddKeyItem(AActor* Piece)
{
}

bool UInventoryComponent::UseItem(UItemBase* Item)
{
    return false;
}

void UInventoryComponent::AddWeapon(AWeaponBase* Weapon)
{
}

void UInventoryComponent::RemoveWeapon(AWeaponBase* Weapon)
{
}

void UInventoryComponent::AddArmor(AArmorBase* Armor)
{
}

void UInventoryComponent::RemoveArmor(AArmorBase* Armor)
{
}

void UInventoryComponent::EquipHandSlot(AWeaponBase* Weapon, AArmorBase* Shield, bool SetLeftHand)
{
}

void UInventoryComponent::UnequipHandSlot(bool SetLeftHand)
{
}

void UInventoryComponent::UnequipArmorSlot(AArmorBase* Armor)
{
}

void UInventoryComponent::EquipArmorSlot(AArmorBase* Armor)
{
}

int32 UInventoryComponent::CountItems(UItemBase* Item)
{
    return int32();
}

int32 UInventoryComponent::CountWeapons(AWeaponBase* Weapon)
{
    return int32();
}

int32 UInventoryComponent::CountArmor(AWeaponBase* Armor)
{
    return int32();
}

TMap<FString, int32> UInventoryComponent::DisplayInventory()
{
    return TMap<FString, int32>();
}
