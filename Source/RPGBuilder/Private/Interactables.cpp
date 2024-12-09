#include "Interactables.h"
#include "CharacterBase.h"
#include "ItemBase.h"
#include "WeaponBase.h"
#include "ArmorBase.h"
#include "Kismet/GameplayStatics.h"

AInteractables::AInteractables()
{
	Name = "DefaultName";
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
}

void AInteractables::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractables::OnOpen()
{
	ACharacterBase* MC = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(this, 0));
	check(MC);
	if (!bHasBeenOpened)
	{
		bHasBeenOpened = true;
		check(OpeningAnim);
		Mesh->PlayAnimation(OpeningAnim, false);
		if (Item)
		{
			UItemBase* ItemRef = Cast<UItemBase>(Item->GetDefaultObject());
			ItemRef->AddToInventory(MC);
		}

		if (Weapon)
		{
			AWeaponBase* WeaponRef = Cast<AWeaponBase>(Weapon);
			WeaponRef->AddToInventory(MC);
		}

		if (Armor)
		{
			AArmorBase* ArmorRef = Cast<AArmorBase>(Armor);
			ArmorRef->AddToInventory(MC);
		}
	}
}

FString AInteractables::GetInteractText()
{
	return FString::Printf(TEXT("%s: Press Action Button To Pickup"), *Name.ToString());
}
