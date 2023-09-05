#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemBase;
class AWeaponBase;
class AArmorBase;
class ACharacterBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RPGBUILDER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	TArray<UItemBase*> ItemsArray;
	TArray<AWeaponBase*> WeaponsArray;
	TArray<AArmorBase*> ArmorArray;

	ACharacterBase* MC;
	
	//Denotes how many instances of an individual item is allowed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Capacity Limits")
	int32 MaxItemCapacity;
	//Denotes how many instances of a piece of armor is allowed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Capacity Limits")
	int32 MaxArmorCapacity;
	//Denotes how many instnaces of an individual weapon is allowed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Capacity Limits")
	int32 MaxWeaponCapacity;

public:

	bool AddItem(UItemBase* Item);

	void RemoveItem(UItemBase* Item);

	void AddKeyItem(AActor* Piece);

	UFUNCTION(BlueprintCallable)
	bool UseItem(UItemBase* Item);

	void AddWeapon(AWeaponBase* Weapon);

	void RemoveWeapon(AWeaponBase* Weapon);

	void AddArmor(AArmorBase* Armor);

	void RemoveArmor(AArmorBase* Armor);
	UFUNCTION(BlueprintCallable)
		void EquipHandSlot(AWeaponBase* Weapon, AArmorBase* Shield, bool SetLeftHand);
	UFUNCTION(BlueprintCallable)
		void UnequipHandSlot(bool SetLeftHand);
	UFUNCTION(BlueprintCallable)
		void UnequipArmorSlot(AArmorBase* Armor);
	UFUNCTION(BlueprintCallable)
		void EquipArmorSlot(AArmorBase* Armor);

	int32 CountItems(UItemBase* Item);

	int32 CountWeapons(AWeaponBase* Weapon);

	int32 CountArmor(AArmorBase* Armor);

	//UInventoryComponent* GetInventoryComponent() { return this; };
	UFUNCTION(BlueprintCallable)
	TMap<FString, int32> DisplayInventory();

};
