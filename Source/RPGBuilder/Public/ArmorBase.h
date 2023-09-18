#pragma once
#include "CoreMinimal.h"
#include "Interactables.h"
#include "ArmorBase.generated.h"

class ACharacterBase;
class USkeletalMeshComponent;
class USoundCue;

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	EAT_BodyArmor UMETA(DisplayName = "Body"),
	EAT_HandArmor UMETA(DisplayName = "Hands"),
	EAT_LegArmor UMETA(DisplayName = "Legs"),
	EAT_FeetArmor UMETA(DisplayName = "Feet"),

	EAT_DEFAULTMAX UMETA(DisplayName = "Default")
};

UCLASS()
class RPGBUILDER_API AArmorBase : public AInteractables
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArmorBase();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		FString ArmorDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		float Defense;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ItemInfo ")
		AController* ArmorInstigator;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		EArmorType ArmorType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo | Buffs")
		EBuffType BuffType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo | Sounds")
		USoundCue* OnEquippedSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool IsArmorTypeSet();
	UFUNCTION(BlueprintCallable)
	void AddToInventory(ACharacterBase* MC);

	FORCEINLINE void SetInstigator(AController* Inst) { ArmorInstigator = Inst; }
};

