#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

class ACharacterBase;
class USoundCue;

UENUM(BlueprintType)
enum class EItemBuffType : uint8
{
	EIBT_HealthBuff UMETA(DisplayName = "Health Buff"),
	EIBT_MagicPointsBuff UMETA(DisplayName = "MP Buff"),
	EIBT_StrengthBuff UMETA(DisplayName = "Strength Buff"),
	EIBT_DefenseBuff UMETA(DisplayName = "Defense Buff"),
	EIBT_AgilityBuff UMETA(DisplayName = "Agility Buff"),
	EIBT_IntelligenceBuff UMETA(DisplayName = "Intelligence Buff"),
	EIBT_StaminaBuff UMETA(DisplayName = "Stamina Buff"),

	EIBT_MAX UMETA(DisplayName = "MAX")
	
};

UENUM(BlueprintType)
enum class EItemDebuffType : uint8
{
	EIDT_HealthDebuff UMETA(DisplayName = "Health Debuff"),
	EIDT_MagicPointsDebuff UMETA(DisplayName = "MP Debuff"),
	EIDT_StrengthDebuff UMETA(DisplayName = "Strength Debuff"),
	EIDT_DefenseDebuff UMETA(DisplayName = "Defense Debuff"),
	EIDT_AgilityDebuff UMETA(DisplayName = "Agility Debuff"),
	EIDT_IntelligenceDebuff UMETA(DisplayName = "Intelligence Debuff"),
	EIDT_StaminaDebuff UMETA(DisplayName = "Stamina Debuff"),

	EIDT_MAX UMETA(DisplayName = "MAX")

};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_HealingItem UMETA(DisplayName = "Healing"),
	EIT_OffensiveItem UMETA(DisplayName = "Offensive"),
	EIT_DefensiveITem UMETA(DisplayName = "Defensive"),
	EIT_KeyItem UMETA(DisplayName = "Key Item"),

	EIT_MAX UMETA(DisplayName = "Default")
};

UCLASS()
class RPGBUILDER_API UItemBase : public UObject
{
	GENERATED_BODY()



public:
	//Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		FName ItemName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		FString ItemDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		int32 Defense;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		int32 Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		int32 Attack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		int32 MagicPoints;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		int32 Intelligence;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		int32 Stamina;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		int32 Strength;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		int32 Agility;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		bool bIsUsable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		float BuffTimer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		EItemType ItemType = EItemType::EIT_MAX;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		EItemBuffType ItemBuffType = EItemBuffType::EIBT_MAX;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		EItemDebuffType ItemDebuffType = EItemDebuffType::EIDT_MAX;

	FTimerHandle BuffTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo | Sounds")
		USoundCue* OnUseSound;
public:
	//Functions

	UItemBase();
	UFUNCTION(BlueprintCallable)
	virtual bool AddBuff(ACharacterBase* MC);
	UFUNCTION(BlueprintCallable)
	virtual bool AddDebuff(ACharacterBase* MC);
	UFUNCTION(BlueprintCallable)
	virtual bool RemoveBuff(ACharacterBase* MC);
	UFUNCTION(BlueprintCallable)
	bool AddToInventory(ACharacterBase* MC);

	FORCEINLINE void SetItemType(EItemType Type) { ItemType = Type; }
};

