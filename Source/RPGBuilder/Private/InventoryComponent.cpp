#include "InventoryComponent.h"
#include "WeaponBase.h"
#include "ArmorBase.h"
#include "ItemBase.h"
#include "CharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Sound/SoundCue.h"

UInventoryComponent::UInventoryComponent()
{

}

bool UInventoryComponent::AddItem(UItemBase* Item)
{
	if (Item != nullptr)
	{
		if (CountItems(Item) != MaxItemCapacity)
		{
			ItemsArray.Add(Item);
			return true;
		}
		return false;
	}
	return false;
}

void UInventoryComponent::RemoveItem(UItemBase* Item)
{
	int32 Index;
	if (ItemsArray.FindLast(Item, Index))
	{
		ItemsArray.RemoveAt(Index);
	}
}

void UInventoryComponent::AddKeyItem(AActor* Piece)
{
}

bool UInventoryComponent::UseItem(UItemBase* Item)
{
	if (Item->AddBuff(MC))
	{
		RemoveItem(Item);
		return true;
	}
	return false;
}

void UInventoryComponent::AddWeapon(AWeaponBase* Weapon)
{
	if (CountWeapons(Weapon) != MaxWeaponCapacity)
	{
		WeaponsArray.Add(Weapon);
	}
}

void UInventoryComponent::RemoveWeapon(AWeaponBase* Weapon)
{
	int32 Index;
	if (WeaponsArray.FindLast(Weapon, Index))
	{
		WeaponsArray.RemoveAt(Index);
	}
}

void UInventoryComponent::AddArmor(AArmorBase* Armor)
{
	if (CountArmor(Armor) != MaxArmorCapacity)
	{
		ArmorArray.Add(Armor);
	}
}

void UInventoryComponent::RemoveArmor(AArmorBase* Armor)
{
	int32 Index;
	if (ArmorArray.FindLast(Armor, Index))
	{
		ArmorArray.RemoveAt(Index);
	}
}

void UInventoryComponent::EquipHandSlot(AWeaponBase* Weapon, AArmorBase* Shield, bool SetLeftHand)
{
    MC = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//TODO: Check if Weapon or Shield is Equipped already, if so Unequip and RemoveBuff
	check(MC);
	if (Weapon)
	{
		AWeaponBase* WeaponToEquip = GetWorld()->SpawnActor<AWeaponBase>(Weapon->StaticClass());
		Weapon->SetInstigator(MC->GetController());
		Weapon->SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		Weapon->SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		Weapon->SkeletalMesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* RightHandSocket = MC->GetMesh()->GetSocketByName(MC->RightHandSocketName);
		const USkeletalMeshSocket* LeftHandSocket = MC->GetMesh()->GetSocketByName(MC->LeftHandSocketName);

		if (!SetLeftHand)
		{
			if (MC->CharacterEquipment.RightWeaponSlot || MC->CharacterEquipment.RightArmorSlot)
			{
				UnequipHandSlot(SetLeftHand);
			}
			check(RightHandSocket);
			RightHandSocket->AttachActor(WeaponToEquip, MC->GetMesh());
			MC->CharacterEquipment.SetWeaponSlot(Weapon, SetLeftHand);
			Weapon->SetWeaponOwner(MC);
			RemoveWeapon(Weapon);
		}
		if (SetLeftHand)
		{
			if (MC->CharacterEquipment.LeftWeaponSlot || MC->CharacterEquipment.LeftArmorSlot)
			{
				UnequipHandSlot(SetLeftHand);
			}
			check(LeftHandSocket);
			LeftHandSocket->AttachActor(WeaponToEquip, MC->GetMesh());
			MC->CharacterEquipment.SetWeaponSlot(Weapon, SetLeftHand);
			Weapon->SetWeaponOwner(MC);
			RemoveWeapon(Weapon);
		}
		if (Weapon->OnEquippedSound)
		{
			UGameplayStatics::PlaySound2D(this, Weapon->OnEquippedSound);
		}
		MC = nullptr;
	}
	if (Shield)
	{
		AArmorBase* ShieldToSpawn = GetWorld()->SpawnActor<AArmorBase>(Shield->StaticClass());
		Shield->SetInstigator(MC->GetController());
		Shield->SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		Shield->SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		Shield->SkeletalMesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* RightHandSocket = MC->GetMesh()->GetSocketByName(MC->RightHandSocketName);
		const USkeletalMeshSocket* LeftHandSocket = MC->GetMesh()->GetSocketByName(MC->LeftHandSocketName);

		if (!SetLeftHand)
		{
			if (MC->CharacterEquipment.RightWeaponSlot || MC->CharacterEquipment.RightArmorSlot)
			{
				UnequipHandSlot(SetLeftHand);
			}
			check(RightHandSocket);
			RightHandSocket->AttachActor(ShieldToSpawn, MC->GetMesh());
			MC->CharacterEquipment.SetShieldSlot(Shield, SetLeftHand);
			RemoveArmor(Shield);
		}
		if (SetLeftHand)
		{
			if (MC->CharacterEquipment.LeftWeaponSlot || MC->CharacterEquipment.LeftArmorSlot)
			{
				UnequipHandSlot(SetLeftHand);
			}
			check(LeftHandSocket);
			LeftHandSocket->AttachActor(ShieldToSpawn, MC->GetMesh());
			MC->CharacterEquipment.SetShieldSlot(Shield, SetLeftHand);
			RemoveArmor(Shield);
		}
		if (Shield->OnEquippedSound)
		{
			UGameplayStatics::PlaySound2D(this, Shield->OnEquippedSound);
		}
		MC = nullptr;
	}




}

void UInventoryComponent::UnequipHandSlot(bool SetLeftHand)
{
    MC = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(this, 0));
    check(MC);
	if (!SetLeftHand && MC->CharacterEquipment.RightWeaponSlot)
	{
		AddWeapon(MC->CharacterEquipment.RightWeaponSlot);
		MC->CharacterEquipment.SetWeaponSlot(nullptr, SetLeftHand);
		MC->CharacterEquipment.RightWeaponSlot->Destroy();
	}
	if (!SetLeftHand && MC->CharacterEquipment.RightArmorSlot)
	{
		AddArmor(MC->CharacterEquipment.RightArmorSlot);
		MC->CharacterEquipment.SetShieldSlot(nullptr, SetLeftHand);
		MC->CharacterEquipment.RightArmorSlot->Destroy();
	}
	if (SetLeftHand && MC->CharacterEquipment.LeftWeaponSlot)
	{
		AddWeapon(MC->CharacterEquipment.LeftWeaponSlot);
		MC->CharacterEquipment.SetWeaponSlot(nullptr, SetLeftHand);
		MC->CharacterEquipment.LeftWeaponSlot->Destroy();
	}
	if (SetLeftHand && MC->CharacterEquipment.LeftArmorSlot)
	{
		AddArmor(MC->CharacterEquipment.LeftArmorSlot);
		MC->CharacterEquipment.SetShieldSlot(nullptr, SetLeftHand);
		MC->CharacterEquipment.LeftArmorSlot->Destroy();
	}
    //Weapon->SetInstigator(nullptr);
   // Weapon->SetWeaponOwner(nullptr);
}

void UInventoryComponent::UnequipArmorSlot(AArmorBase* Armor)
{
	switch (Armor->ArmorType)
	{
	case EArmorType::EAT_BodyArmor:
		AddArmor(MC->CharacterEquipment.BodySlot);
		MC->CharacterEquipment.SetBodyArmorSlot(nullptr);
		break;
	case EArmorType::EAT_HandArmor:
		AddArmor(MC->CharacterEquipment.HandSlot);
		MC->CharacterEquipment.SetHandSlot(nullptr);
		break;
	case EArmorType::EAT_LegArmor:
		AddArmor(MC->CharacterEquipment.LegSlot);
		MC->CharacterEquipment.SetLegSlot(nullptr);
		break;
	case EArmorType::EAT_FeetArmor:
		AddArmor(MC->CharacterEquipment.FeetSlot);
		MC->CharacterEquipment.SetFeetSlot(nullptr);
		break;
	default:
		break;
	}
}

void UInventoryComponent::EquipArmorSlot(AArmorBase* Armor)
{
	//TODO: Check if Armor is Equipped already, if so Unequip and RemoveBuff
	check(MC);
	check(Armor);
	check(Armor->IsArmorTypeSet());
	switch (Armor->ArmorType)
	{
	case EArmorType::EAT_BodyArmor:
		if (MC->CharacterEquipment.BodySlot)
		{
			UnequipArmorSlot(Armor);
		}
		MC->CharacterEquipment.SetBodyArmorSlot(Armor);
		RemoveArmor(Armor);
		break;
	case EArmorType::EAT_HandArmor:
		if (MC->CharacterEquipment.HandSlot)
		{
			UnequipArmorSlot(Armor);
		}
		MC->CharacterEquipment.SetHandSlot(Armor);
		RemoveArmor(Armor);
		break;
	case EArmorType::EAT_LegArmor:
		if (MC->CharacterEquipment.LegSlot)
		{
			UnequipArmorSlot(Armor);
		}
		MC->CharacterEquipment.SetLegSlot(Armor);
		RemoveArmor(Armor);
		break;
	case EArmorType::EAT_FeetArmor:
		if (MC->CharacterEquipment.FeetSlot)
		{
			UnequipArmorSlot(Armor);
		}
		MC->CharacterEquipment.SetFeetSlot(Armor);
		RemoveArmor(Armor);
		break;
	default:
		break;
	}
}

int32 UInventoryComponent::CountItems(UItemBase* Item)
{
	int32 ItemCount = 0;
	for (int32 i = 0; i < ItemsArray.Num(); ++i)
	{
		if (ItemsArray[i]->ItemName == Item->ItemName)
		{
			++ItemCount;
		}
	}
	return ItemCount;
}

int32 UInventoryComponent::CountWeapons(AWeaponBase* Weapon)
{
	int32 ItemCount = 0;
	for (int32 i = 0; i < WeaponsArray.Num(); ++i)
	{
		if (WeaponsArray[i]->Name == Weapon->Name)
		{
			++ItemCount;
		}
	}
	return ItemCount;
}

int32 UInventoryComponent::CountArmor(AArmorBase* Armor)
{
	int32 ItemCount = 0;
	for (int32 i = 0; i < ArmorArray.Num(); ++i)
	{
		if (ArmorArray[i]->Name == Armor->Name)
		{
			++ItemCount;
		}
	}
	return ItemCount;
}

TMap<FString, int32> UInventoryComponent::DisplayInventory()
{
	FName OldName;
	FName NewName;
	int32 ItemCount;
	TMap<FString, int32> StringMap;

	for (int32 i = 0; i < ItemsArray.Num(); ++i)
	{
		NewName = ItemsArray[i]->ItemName;
		ItemCount = CountItems(ItemsArray[i]);
		if (i >= 1)
		{
			OldName = ItemsArray[i - 1]->ItemName;
		}
		if (OldName == FName("None") && i != 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Count: %d"), *NewName.ToString(), ItemCount)
				StringMap.Add(NewName.ToString(), ItemCount);

		}
		if (OldName != NewName)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Count: %d"), *NewName.ToString(), ItemCount)
				StringMap.Add(NewName.ToString(), ItemCount);
		}
	}
	return StringMap;
}
