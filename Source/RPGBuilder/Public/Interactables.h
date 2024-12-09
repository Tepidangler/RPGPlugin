#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactables.generated.h"

class UItemBase;
class AWeaponBase;
class AArmorBase;
class USkeletalMeshComponent;
class UAnimSequence;
class ACharacterBase;

UENUM(BlueprintType)
enum class EBuffType : uint8
{
	EBT_Agility UMETA(DisplayName = "Agility Buff"),
	EBT_Strength UMETA(DisplayName = "Strength Buff"),
	EBT_Health UMETA(DisplayName = "Health Buff"),
	EBT_Defense UMETA(DisplayName = "Defense BUff"),
	EBT_MagicPoints UMETA(DisplayName = "MP Buff"),
	EBT_Intelligence  UMETA(DisplayName = "Intelligence Buff"),

	EBT_MAX UMETA(DisplayName = "Default MAX")
};

UCLASS()
class RPGBUILDER_API AInteractables : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractables();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemInfo")
		bool bIsEquipped = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo | Loot")
		TSubclassOf<UItemBase> Item;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo | Loot")
		TSubclassOf<AWeaponBase> Weapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo | Loot")
		TSubclassOf<AArmorBase> Armor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemInfo | Mesh")
		USkeletalMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemInfo | Animation")
		UAnimSequence* OpeningAnim;

	bool bHasBeenOpened = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void OnOpen();
	UFUNCTION(BlueprintCallable)
	FString GetInteractText();


};

