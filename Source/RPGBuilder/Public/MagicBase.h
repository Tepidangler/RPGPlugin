#pragma once
#include "CoreMinimal.h"
#include "GameFrameWork/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "MagicBase.generated.h"

UENUM(Blueprintable)
enum class EMagicBuffType : uint8
{
	EMBT_HealthBuff UMETA(DisplayName = "Health Buff"),
	EMBT_MagicPointsBuff UMETA(DisplayName = "MP Buff"),
	EMBT_StrengthBuff UMETA(DisplayName = "Strength Buff"),
	EMBT_DefenseBuff UMETA(DisplayName = "Defense Buff"),
	EMBT_AgilityBuff UMETA(DisplayName = "Agility Buff"),
	EMBT_IntelligenceBuff UMETA(DisplayName = "Intelligence Buff"),
	EMBT_StaminaBuff UMETA(DisplayName = "Stamina Buff"),

	EMBT_MAX UMETA(DisplayName = "MAX")
};

UENUM(Blueprintable)
enum class EMagicDebuffType : uint8
{
	EMDT_HealthBuff UMETA(DisplayName = "Health Debuff"),
	EMDT_MagicPointsBuff UMETA(DisplayName = "MP Debuff"),
	EMDT_StrengthBuff UMETA(DisplayName = "Strength Debuff"),
	EMDT_DefenseBuff UMETA(DisplayName = "Defense Debuff"),
	EMDT_AgilityBuff UMETA(DisplayName = "Agility Debuff"),
	EMDT_IntelligenceBuff UMETA(DisplayName = "Intelligence Debuff"),
	EMDT_StaminaBuff UMETA(DisplayName = "Stamina Debuff"),

	EMDT_MAX UMETA(DisplayName = "MAX")
};

class ACharacterBase;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class RPGBUILDER_API AMagicBase : public AActor
{
	GENERATED_BODY()

public:
	AMagicBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void AddBuff();
	UFUNCTION(BlueprintCallable)
	void AddDebuff();
	UFUNCTION(BlueprintCallable)
	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	FORCEINLINE void SetCaster(AActor* Actor) { Caster = Actor; }
	FORCEINLINE void SetInstigator(AController* Inst) { MagicInstigator = Inst; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		USphereComponent* CollisionComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particles")
		UParticleSystemComponent* ParticleSystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilityInfo")
		AActor* Caster = nullptr;
	AController* MagicInstigator = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo")
		FName Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo")
		float Cost;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo")
		float CastTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo", meta = (ClampMin= "1.0", ClampMax= "2.0"))
		float BuffMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo", meta = (ClampMin = "0.05", ClampMax = "1.0"))
		float DebuffMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo")
		bool bIsRestoritive = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo | BuffType")
		EMagicBuffType BuffType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo | BuffType")
		EMagicDebuffType DebuffType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo | DamageType")
		TSubclassOf<UDamageType> DamageTypeClass;


};

