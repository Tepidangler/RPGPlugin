#pragma once
#include "CoreMinimal.h"
#include "Interactables.h"
#include "WeaponBase.generated.h"

class ACharacterBase;
class AEnemyBase;
class USkeletalMeshComponent;
class USoundCue;
class UBoxComponent;

UCLASS()
class RPGBUILDER_API AWeaponBase : public AInteractables
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		FString WeaponDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo")
		float Attack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo | Buff")
		EBuffType BuffType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		AController* WeaponInstigator;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		ACharacterBase* WeaponOwner;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo | Components")
		USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ItemInfo | Components")
		UBoxComponent* CollisionComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemInfo | Sounds")
		USoundCue* OnEquippedSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemInfo | DamageType")
		TSubclassOf<UDamageType> DamageTypeClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemInfo | Particles")
		UParticleSystem* BlockParticles;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemInfo | Particles")
		UParticleSystem* HitWorldParticles;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void AddToInventory(ACharacterBase* MC);

	FORCEINLINE void SetInstigator(AController* Inst) { WeaponInstigator = Inst; }

	FORCEINLINE void SetWeaponOwner(ACharacterBase* MC) { WeaponOwner = MC; }
};

