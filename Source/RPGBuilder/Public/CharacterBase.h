#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ItemBase.h"
#include "MagicBase.h"
#include "CharacterBase.generated.h"

USTRUCT(BlueprintType)
struct FCharacterEquipment
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Character Equipment")
		class AWeaponBase* LeftWeaponSlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Character Equipment")
		AWeaponBase* RightWeaponSlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Character Equipment")
		class AArmorBase* LeftArmorSlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Character Equipment")
		AArmorBase* RightArmorSlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Character Equipment")
		AArmorBase* BodySlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Character Equipment")
		AArmorBase* HandSlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Character Equipment")
		AArmorBase* LegSlot = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Character Equipment")
		AArmorBase* FeetSlot = nullptr;

	void SetWeaponSlot(AWeaponBase* Weapon, bool SetLeftHand)
	{
		//Wielding Status should be set when eqipping/removing the weapon
		if (SetLeftHand)
		{
			LeftWeaponSlot = Weapon;
		}
		else
		{
			RightWeaponSlot = Weapon;
		}

	}

	void SetShieldSlot(AArmorBase* Armor, bool SetLeftHand)
	{
		if (SetLeftHand && !RightArmorSlot)
		{
			LeftArmorSlot = Armor;
		}
		if (!SetLeftHand && !LeftArmorSlot)
		{
			RightArmorSlot = Armor;
		}
	}

	void SetBodyArmorSlot(AArmorBase* Armor)
	{
		BodySlot = Armor;
	}

	void SetHandSlot(AArmorBase* Armor)
	{
		HandSlot = Armor;
	}

	void SetLegSlot(AArmorBase* Armor)
	{
		LegSlot = Armor;
	}

	void SetFeetSlot(AArmorBase* Armor)
	{
		FeetSlot = Armor;
	}
};

UENUM(BlueprintType)
enum class EWeaponWieldingStatus : uint8
{
	EWWS_SingleWield UMETA(DisplayName = "SingleWield"),
	EWWS_DualWield UMETA(DisplayName = "DualWield"),

	EWWS_MAX UMETA(DisplayName = "DefaultMAX")
};
UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_Fatigued UMETA(DisplayName = "Fatigued"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering UMETA(DisplayName = "ExhaustedRecovering"),

	ESS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_NoMovement UMETA(DisplayName = "NoMovement"),
	EMS_Walking UMETA(DisplayName = "Walking"),
	EMS_Running UMETA(DisplayName = "Running"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),
	EMS_Dead UMETA(DisplayName = "Dead"),

	EMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EPositionStatus : uint8
{
	EPS_Standing UMETA(DisplayName = "Standing"),
	EPS_Crouching UMETA(DisplayName = "Crouching"),

	EPS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class ELockOnStatus : uint8
{
	ELS_LockedOn UMETA(DisplayName = "LockedOn"),
	ELS_NotLockedOn UMETA(DisplayName = "NotLockedOn"),

	ELS_MAX UMETA(DisplayName = "DefaultMAX")
};

class UStatsComponent;
class UASComponent;
class UMagicSystemComponent;



UCLASS()
class RPGBUILDER_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UStatsComponent* StatsComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		UMagicSystemComponent* MagicSystemComponent = nullptr;
	//UPROPERTY()
	//	class AAlifPlayerController* PC = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		class UInventoryComponent* Inventory;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
		class UAnimMontage* CombatMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		class USoundCue* SwingSwordEffortSound;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	//	class AEnemyBase* CombatTarget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		float BaseTurnRate = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		float BaseLookUpRate = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Raycast")
		float RaycastRange = 300.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement | Sprinting")
		float MinSprintStamina = 20.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement | Sprinting")
		float StaminaDrainRate = 5.f;
	//UPROPERTY()
	//	float StealthRating = 1.f;
	UPROPERTY()
		FVector LateralSpeed = FVector(0.f, 0.f, 0.f);
	UPROPERTY()
		float MovementSpeed = 0.f;

	float SprintingSpeed = 600.f;

	float RunningSpeed = 500.f;

	float ButtonDownTime = 0.f;

	float InterpSpeed = 15.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
		EMovementStatus MovementStatus;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
		EStaminaStatus StaminaStatus;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
		EWeaponWieldingStatus WieldingStatus;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
		EPositionStatus PositionStatus;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
		ELockOnStatus LockOnStatus = ELockOnStatus::ELS_NotLockedOn;
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Struct | Stats")
//		FCharacterStats CharacterStats;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Struct | Equipment")
		FCharacterEquipment CharacterEquipment;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bSprinting = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bMovingForward = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bMovingRight = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Action")
		bool bActionButtonDown = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool bAttacking = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Action")
		bool bCanceling = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool bIsComboStarted = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool bInterpToEnemy = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat | Particles")
		UParticleSystem* HitParticles;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		USoundCue* CancelSound = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetInterpToEnemy(bool Interp);

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	virtual void Jump() override;
	virtual void StopJumping() override;

	void ActionDown();

	void ActionUp();

	void SprintDown();

	void SprintUp();

	void CancelDown();

	void CancelUp();

	void AttackDown();

	void AttackUp();

	void Attack();

	void LockOnDown();

	void LockOnUp();

	FRotator GetLookAtRotationYaw(FVector Target);

	//Getter/Setter MovementStatus Enum
	FORCEINLINE EMovementStatus GetMovementStatus() { return MovementStatus; };
	void SetMovementStatus(float Speed);

	//Getter/Setter StaminaStatus Enum
	FORCEINLINE EStaminaStatus GetStaminaStatus() { return StaminaStatus; };
	void SetStaminaStatus(EStaminaStatus Status);
	//Getter/Setter WeaponWieldingStatus Enum
	FORCEINLINE EWeaponWieldingStatus GetWieldingStatus() { return WieldingStatus; };

	void SetWieldingStatus(EWeaponWieldingStatus Status);

	//Getter/Setter PositionStatus Enum
	FORCEINLINE EPositionStatus GetPositionStatus() { return PositionStatus; };

	void SetPositionStatus(EPositionStatus Status);

	FORCEINLINE ELockOnStatus GetLockOnStatus() { return LockOnStatus; };

	void SetLockOnStatus(ELockOnStatus Status);

	void CalculateStealthRating(EMovementStatus Status, EPositionStatus Position);

	void CheckForInteractables();

	void CheckForEnemy();
	//Uses Multiplication rather than addition
	void AddMagicBuff(float Value, EMagicBuffType Type);

	void AddMagicDebuff(float Value, EMagicDebuffType Type);
	//Uses Addition rather than multiplication
	void AddItemBuff(float Value, EItemBuffType Type);
	void AddItemDebuff(float Value, EItemDebuffType Type);

	void ApplyDamage(float Damage);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "Character Animations")
	void Die();

	bool IsDead();


};

