#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MagicSystemComponent.h"
#include "ASComponent.h"
#include "EnemyBase.generated.h"

class UStatsComponent;

UCLASS()
class RPGBUILDER_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
		float CalculatePhysicalDamage(ACharacterBase* MC);


		virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

		void Die(AActor* Causer);
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
		UStatsComponent* StatsComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Magic, meta = (AllowPrivateAccess = "true"))
		UMagicSystemComponent* MagicComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyInfo | DamageType")
		TSubclassOf<UDamageType> DamageTypeClass;


	float Attack;
};

