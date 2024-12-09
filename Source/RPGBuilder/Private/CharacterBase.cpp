#include "CharacterBase.h"
#include "InventoryComponent.h"
#include "ItemBase.h"
#include "WeaponBase.h"
#include "EnemyBase.h"
#include "Interactables.h"
#include "AIController.h"
#include "RPGGameInstance.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StatsComponent.h"
#include "ASComponent.h"
#include "MagicSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Sound/SoundCue.h"

ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Player Inventory"));

	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));

	MagicSystemComponent = CreateDefaultSubobject<UMagicSystemComponent>(TEXT("Magic System Component"));
	MagicSystemComponent->Controller = GetController();

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;




}


// Called when the game starts or when spawned 
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AAIController>(GetController());
	//PC = Cast<AAlifPlayerController>(GetController());

	//UAlifGameInstance* GameInstance = Cast<UAlifGameInstance>(GetGameInstance());
	/**
	check(GameInstance);
	if (GameInstance->CurrentSaveGame && !GameInstance->bIsMovingToInteriorMap)
	{
		GameInstance->LoadGameNoSwitch(true, GameInstance->CurrentSaveGame->SlotName);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Red, FString("LoadGameNoSwitch() SetPosition =  True"));
		return;
	}
	if (GameInstance->CurrentSaveGame && GameInstance->bIsMovingToInteriorMap)
	{
		GameInstance->bIsMovingToInteriorMap = false;
		GameInstance->LoadGameNoSwitch(false, GameInstance->CurrentSaveGame->SlotName);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Red, FString("LoadGameNoSwitch() SetPosition =  False"));
	}
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Red, FString("LoadGameNoSwitch() NotHit"));
	*/

	//PC->DisplayHUDOverlay();


}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CombatStatus != ECombatStatus::ECS_InCombat && ControllerType == EControlledType::ECT_AIControlled)
	{
		FollowPrimaryCharacter();
	}

	if (LockOnStatus == ELockOnStatus::ELS_NotLockedOn)
	{
		CheckForInteractables();
	}

	if (bActionButtonDown && ButtonDownTime < 1.f)
	{
		ButtonDownTime += .1f;
	}
	LateralSpeed = FVector(GetVelocity().X, GetVelocity().Y, 0.f);
	MovementSpeed = LateralSpeed.Size();

	float DeltaStamina = StaminaDrainRate * DeltaTime;
	switch (StaminaStatus)
	{
	case EStaminaStatus::ESS_Normal:
		if (bSprinting)
		{
			if (bMovingForward || bMovingRight)
			{
				if (StatsComponent->CurrentStamina - DeltaStamina <= MinSprintStamina)
				{
					SetStaminaStatus(EStaminaStatus::ESS_Fatigued);
					StatsComponent->CurrentStamina -= DeltaStamina;
				}
				else
				{
					StatsComponent->CurrentStamina -= DeltaStamina;
				}
				if (bMovingForward || bMovingRight)
				{
					SetMovementStatus(MovementSpeed);
				}
				else
				{
					SetMovementStatus(MovementSpeed);
				}
			}
			else // Shift Key Up 
			{
				if (StatsComponent->CurrentStamina + DeltaStamina >= StatsComponent->Stamina.GetValueAtLevel(StatsComponent->Level))
				{
					StatsComponent->CurrentStamina = StatsComponent->Stamina.GetValueAtLevel(StatsComponent->Level);
				}
				else
				{
					StatsComponent->CurrentStamina += DeltaStamina;
				}
				SetMovementStatus(MovementSpeed);
			}

		}
		else // Shift Key Up 
		{
			if (StatsComponent->CurrentStamina + DeltaStamina >= StatsComponent->Stamina.GetValueAtLevel(StatsComponent->Level))
			{
				StatsComponent->CurrentStamina = StatsComponent->Stamina.GetValueAtLevel(StatsComponent->Level);
			}
			else
			{
				StatsComponent->CurrentStamina += DeltaStamina;
			}
			SetMovementStatus(MovementSpeed);
		}
		break;
	case EStaminaStatus::ESS_Fatigued:
		if (bSprinting)
		{
			if (bMovingForward || bMovingRight)
			{
				if (StatsComponent->CurrentStamina - DeltaStamina <= 0.f)
				{
					SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
					StatsComponent->CurrentStamina = 0.f;
					SetMovementStatus(MovementSpeed);
				}
				else // Otherwise just decrement stamina
				{
					StatsComponent->CurrentStamina -= DeltaStamina;
					if (bMovingForward || bMovingRight)
					{
						SetMovementStatus(MovementSpeed);
					}
					else
					{
						SetMovementStatus(MovementSpeed);
					}
				}
			}
			else //NOT Moving Right/Left OR Forward/Backward
			{
				if (StatsComponent->CurrentStamina + DeltaStamina >= MinSprintStamina)
				{
					SetStaminaStatus(EStaminaStatus::ESS_Normal);
					StatsComponent->CurrentStamina += DeltaStamina;
				}
				else
				{
					StatsComponent->CurrentStamina += DeltaStamina;
				}
				SetMovementStatus(MovementSpeed);
			}

		}
		else //Shift Key Up
		{
			if (StatsComponent->CurrentStamina + DeltaStamina >= MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
				StatsComponent->CurrentStamina += DeltaStamina;
			}
			else
			{
				StatsComponent->CurrentStamina += DeltaStamina;
			}
			SetMovementStatus(MovementSpeed);
		}
		break;
	case EStaminaStatus::ESS_Exhausted:
		if (bSprinting)
		{
			if (bMovingForward || bMovingRight)
			{
				StatsComponent->CurrentStamina = 0.f;
			}
			else //Moving Right/Left OR Forward/Backward
			{
				SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
				StatsComponent->CurrentStamina += DeltaStamina;
			}
		}
		else //Shift Key Up
		{
			SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
			StatsComponent->CurrentStamina += DeltaStamina;
		}
		SetMovementStatus(MovementSpeed);
		break;
	case EStaminaStatus::ESS_ExhaustedRecovering:
		if (StatsComponent->CurrentStamina + DeltaStamina >= MinSprintStamina)
		{
			SetStaminaStatus(EStaminaStatus::ESS_Normal);
			StatsComponent->CurrentStamina += DeltaStamina;
		}
		else
		{
			StatsComponent->CurrentStamina += DeltaStamina;
		}
		SetMovementStatus(MovementSpeed);
		break;

	default:
		;
	}
	SetMovementStatus(MovementSpeed);
	CalculateStealthRating(MovementStatus, PositionStatus);
	CheckForEnemy();

	if (bInterpToEnemy)
	{
		/**
		if (CombatTarget)
		{
			FRotator LookAtYaw = GetLookAtRotationYaw(CombatTarget->GetActorLocation());
			FRotator InterpRotation = FMath::RInterpTo(GetActorRotation(), LookAtYaw, DeltaTime, InterpSpeed);

			SetActorRotation(InterpRotation);
			PC->EnemyLocation = CombatTarget->GetMesh()->GetBoneLocation("head");
		}
		*/


	}

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterBase::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacterBase::StopJumping);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ACharacterBase::ActionDown);
	PlayerInputComponent->BindAction("Action", IE_Released, this, &ACharacterBase::ActionUp);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACharacterBase::SprintDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACharacterBase::SprintUp);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterBase::AttackDown);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ACharacterBase::AttackUp);
	PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &ACharacterBase::LockOnDown);
	PlayerInputComponent->BindAction("LockOn", IE_Released, this, &ACharacterBase::LockOnUp);
	PlayerInputComponent->BindAction("Cancel", IE_Pressed, this, &ACharacterBase::CancelDown);
	PlayerInputComponent->BindAction("Cancel", IE_Released, this, &ACharacterBase::CancelUp);


	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACharacterBase::LookUpAtRate);

}

void ACharacterBase::SetInterpToEnemy(bool Interp)
{
	bInterpToEnemy = Interp;
}

void ACharacterBase::TurnAtRate(float Rate)
{
	//if (PC->GetMenuStatus() == EMenuStatus::EMS_MAX)
	//{
		// calculate delta for this frame from the rate information
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
//	}

}

void ACharacterBase::LookUpAtRate(float Rate)
{
	//if (PC->GetMenuStatus() == EMenuStatus::EMS_MAX)
	//{
		// calculate delta for this frame from the rate information
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	//}



}

void ACharacterBase::Jump()
{
	//if (PC->GetMenuStatus() == EMenuStatus::EMS_MAX)
	//{
		Super::Jump();
	//}
}

void ACharacterBase::StopJumping()
{
	Super::StopJumping();
}

void ACharacterBase::ActionDown()
{
	bActionButtonDown = true;
}

void ACharacterBase::ActionUp()
{
	bActionButtonDown = false;
/**
	if (PC->CurrentInteractable)
	{
		PC->CurrentInteractable->OnOpen();
	}
*/
	ButtonDownTime = 0.f;

}

void ACharacterBase::SprintDown()
{
	if (!bSprinting)
	{
		bSprinting = true;
	}
}

void ACharacterBase::SprintUp()
{
	if (bSprinting)
	{
		bSprinting = false;
	}
}

void ACharacterBase::CancelDown()
{

}

void ACharacterBase::CancelUp()
{

}

void ACharacterBase::AttackDown()
{
	if (!IsDead()) return;

	if (!bAttacking)
	{
		if (CharacterEquipment.LeftWeaponSlot || CharacterEquipment.RightWeaponSlot)
		{
			Attack();
		}
	}
}

void ACharacterBase::AttackUp()
{
	bAttacking = false;
}

void ACharacterBase::LockOnDown()
{
	/**
	if (!CombatTarget)
	{
		CheckForEnemy();
	}
	*/

	/**
	switch (LockOnStatus)
	{
	case ELockOnStatus::ELS_LockedOn:
		SetInterpToEnemy(false);
		SetLockOnStatus(ELockOnStatus::ELS_NotLockedOn);
		PC->ToggleLockOnOverlay();
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Blue, FString("LockOn Deactivated"));
		break;
	case ELockOnStatus::ELS_NotLockedOn:
		if (CombatTarget)
		{
			SetInterpToEnemy(true);
			SetLockOnStatus(ELockOnStatus::ELS_LockedOn);
			PC->ToggleLockOnOverlay();
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Blue, FString("LockOn Activated"));
		}
		break;

	default:
		break;
	}
	*/
}

void ACharacterBase::LockOnUp()
{
}


FRotator ACharacterBase::GetLookAtRotationYaw(FVector Target)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target);
	FRotator LookAtRotationYaw(0.f, LookAtRotation.Yaw, 0.f);
	return LookAtRotationYaw;
}

void ACharacterBase::Attack()
{
	
}

void ACharacterBase::SetMovementStatus(float Speed)
{

}

void ACharacterBase::SetStaminaStatus(EStaminaStatus Status)
{
	StaminaStatus = Status;
}

void ACharacterBase::SetWieldingStatus(EWeaponWieldingStatus Status)
{
	WieldingStatus = Status;
}

void ACharacterBase::SetPositionStatus(EPositionStatus Status)
{
	PositionStatus = Status;
}

void ACharacterBase::SetLockOnStatus(ELockOnStatus Status)
{
	LockOnStatus = Status;
}

void ACharacterBase::SetControllerType(EControlledType Type)
{
	ControllerType = Type;
}

void ACharacterBase::SetCombatStatus(ECombatStatus Status)
{
	CombatStatus = Status;
}


void ACharacterBase::CalculateStealthRating(EMovementStatus Status, EPositionStatus Position)
{
	
}

float ACharacterBase::CalculatePhysicalDamage()
{
	float BaseDamage;
	float Damage1;
	float Damage2;
	float AttackBonus;
	float PhysicalBaseModifier = StatsComponent->Strength.GetCurrentValue() - StatsComponent->Strength.GetValueAtLevel(StatsComponent->Level);
	check(CombatTarget)
	//Physical Defense
	float EnemyDefenseModifier = CombatTarget->StatsComponent->Defense.GetCurrentValue() - StatsComponent->Defense.GetValueAtLevel(CombatTarget->StatsComponent->Level);
	if (EnemyDefenseModifier <= 0.f)
	{
		EnemyDefenseModifier = 1.f;
	}

	float EnemyDefense = (CombatTarget->StatsComponent->Defense.GetValueAtLevel(CombatTarget->StatsComponent->Level) * (100 + EnemyDefenseModifier)) / 100;
	if (PhysicalBaseModifier <= 0.f)
	{
		PhysicalBaseModifier = 1.f;
	}

	//Base Damage = Att + [(Att + Lvl) / 32] * [(Att * Lvl) / 32]
	//Damage = [Base Damage * (100 + Physical Base Mod) / 100

	if (CharacterEquipment.LeftWeaponSlot)
	{
		AttackBonus = CharacterEquipment.LeftWeaponSlot->Attack + StatsComponent->Strength.GetValueAtLevel(StatsComponent->Level);
		BaseDamage = AttackBonus + ((AttackBonus + StatsComponent->Level) / 32) * ((AttackBonus * StatsComponent->Level) / 32);
		Damage1 = ((BaseDamage * (100 * PhysicalBaseModifier)) / 100);
		Damage2 = (Damage1 * (512 - EnemyDefense)) / 512;
		return Damage2;
	}
	else
	{
		AttackBonus = CharacterEquipment.RightWeaponSlot->Attack + StatsComponent->Strength.GetValueAtLevel(StatsComponent->Level);
		BaseDamage = AttackBonus + ((AttackBonus + StatsComponent->Level) / 32) * ((AttackBonus * StatsComponent->Level) / 32);
		Damage1 = ((BaseDamage * (100 * PhysicalBaseModifier)) / 100);
		Damage2 = (Damage1 * (512 - EnemyDefense)) / 512;
		return Damage2;
	}
}

float ACharacterBase::CalculateMagicalDamage()
{
	float BaseDamage;
	float Damage1;
	float Damage2;
	float MagicBaseModifier = StatsComponent->MagicAttack.GetCurrentValue() - StatsComponent->MagicAttack.GetValueAtLevel(StatsComponent->Level);
	//Magic Defense
	float EnemyDefenseModifier = CombatTarget->StatsComponent->MagicDefense.GetCurrentValue() - StatsComponent->MagicDefense.GetValueAtLevel(CombatTarget->StatsComponent->Level);
	if (EnemyDefenseModifier <= 0.f)
	{
		EnemyDefenseModifier = 1.f;
	}

	float EnemyDefense = (CombatTarget->StatsComponent->MagicDefense.GetValueAtLevel(CombatTarget->StatsComponent->Level) * (100 + EnemyDefenseModifier)) / 100;
	if (MagicBaseModifier <= 0.f)
	{
		MagicBaseModifier = 1.f;
	}
	//Base Damage = 6 * (MAt + Lvl)
	//Damage = [Base Damage * (100 + Magical Base Mod) / 100]

	BaseDamage = 6 * (StatsComponent->MagicAttack.GetValueAtLevel(StatsComponent->Level) + StatsComponent->Level);
	Damage1 = (BaseDamage * (100 + MagicBaseModifier)) / 100;
	Damage2 = (Damage1 * (512 - EnemyDefense)) / 512;
	return Damage2;
}

void ACharacterBase::CheckForInteractables()
{
	FVector CamLocation;
	FRotator CamRotation;
	FHitResult Hit(ForceInit);


	if (Controller)
	{
		Controller->GetPlayerViewPoint(CamLocation, CamRotation);
		const FVector CharacterEyes = GetMesh()->GetBoneLocation(FName("head"));
		const FVector TraceStart = CharacterEyes;
		const FVector Direction = CamRotation.Vector();
		const FVector TraceEnd = TraceStart + (Direction * RaycastRange);

		FCollisionQueryParams TraceQueryParams(TEXT("TraceInteractableActor"), true, this);
		TraceQueryParams.bReturnPhysicalMaterial = false;
		TraceQueryParams.bTraceComplex = false;
		TraceQueryParams.AddIgnoredActor(this);
		//Check if something is hit
		GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, TraceQueryParams);
		AInteractables* Interactable = Cast<AInteractables>(Hit.GetActor());
		//Check if Valid
		if (Interactable && !Interactable->bIsEquipped)
		{
//			CurrentInteractable = Interactable;
	//		return;
		}
		
		//CurrentInteractable = nullptr;
	}
}

void ACharacterBase::CheckForEnemy()
{
	FVector CamLocation;
	FRotator CamRotation;
	FHitResult Hit(ForceInit);


	if (Controller)
	{
		Controller->GetPlayerViewPoint(CamLocation, CamRotation);
		const FVector CharacterEyes = GetMesh()->GetBoneLocation(FName("head"));
		const FVector TraceStart = CharacterEyes;
		const FVector Direction = CamRotation.Vector();
		const FVector TraceEnd = TraceStart + (Direction * RaycastRange);

		FCollisionQueryParams TraceQueryParams(TEXT("TraceEnemyActor"), true, this);
		TraceQueryParams.bReturnPhysicalMaterial = false;
		TraceQueryParams.bTraceComplex = false;
		TraceQueryParams.AddIgnoredActor(this);
		//Check if something is hit
		GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, TraceQueryParams);
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 5.f);
		AEnemyBase* Enemy = Cast<AEnemyBase>(Hit.GetActor());
		//Check if Valid
		
		if (Enemy)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Enemy"))
			CombatTarget = Enemy;
			return;
		}
		
	}

}

void ACharacterBase::AddItemBuff(float Value, EItemBuffType Type)
{
	switch (Type)
	{
	case EItemBuffType::EIBT_HealthBuff:
		StatsComponent->AddItemBuff(Value, Type);

	case EItemBuffType::EIBT_MagicPointsBuff:
		StatsComponent->AddItemBuff(Value, Type);

	case EItemBuffType::EIBT_StrengthBuff:
		StatsComponent->AddItemBuff(Value, Type);

	case EItemBuffType::EIBT_DefenseBuff:
		StatsComponent->AddItemBuff(Value, Type);

	case EItemBuffType::EIBT_AgilityBuff:
		StatsComponent->AddItemBuff(Value, Type);

	case EItemBuffType::EIBT_IntelligenceBuff:
		StatsComponent->AddItemBuff(Value, Type);

	case EItemBuffType::EIBT_StaminaBuff:
		StatsComponent->AddItemBuff(Value, Type);

	default:
		break;
	}
}

void ACharacterBase::AddItemDebuff(float Value, EItemDebuffType Type)
{

		switch (Type)
		{
		case EItemDebuffType::EIDT_HealthDebuff:
			StatsComponent->AddItemDebuff(Value, Type);

		case EItemDebuffType::EIDT_MagicPointsDebuff:
			StatsComponent->AddItemDebuff(Value, Type);

		case EItemDebuffType::EIDT_StrengthDebuff:
			StatsComponent->AddItemDebuff(Value, Type);

		case EItemDebuffType::EIDT_DefenseDebuff:
			StatsComponent->AddItemDebuff(Value, Type);

		case EItemDebuffType::EIDT_AgilityDebuff:
			StatsComponent->AddItemDebuff(Value, Type);

		case EItemDebuffType::EIDT_IntelligenceDebuff:
			StatsComponent->AddItemDebuff(Value, Type);

		case EItemDebuffType::EIDT_StaminaDebuff:
			StatsComponent->AddItemDebuff(Value, Type);

		default:
			break;
		}
}

void ACharacterBase::AddMagicBuff(float Value, EMagicBuffType Type)
{
	switch (Type)
	{
	case EMagicBuffType::EMBT_HealthBuff:
		StatsComponent->AddMagicBuff(Value, Type);
		break;
	case EMagicBuffType::EMBT_MagicPointsBuff:
		StatsComponent->AddMagicBuff(Value, Type);
		break;
	case EMagicBuffType::EMBT_StrengthBuff:
		StatsComponent->AddMagicBuff(Value, Type);
		break;
	case EMagicBuffType::EMBT_DefenseBuff:
		StatsComponent->AddMagicBuff(Value, Type);
		break;
	case EMagicBuffType::EMBT_AgilityBuff:
		StatsComponent->AddMagicBuff(Value, Type);
		break;
	case EMagicBuffType::EMBT_IntelligenceBuff:
		StatsComponent->AddMagicBuff(Value, Type);
		break;
	case EMagicBuffType::EMBT_StaminaBuff:
		StatsComponent->AddMagicBuff(Value, Type);
		break;
	default:
		break;
	}
}

void ACharacterBase::AddMagicDebuff(float Value, EMagicDebuffType Type)
{
	switch (Type)
	{
	case EMagicDebuffType::EMDT_HealthBuff:
		StatsComponent->AddMagicDebuff(Value, Type);
		break;
	case EMagicDebuffType::EMDT_MagicPointsBuff:
		StatsComponent->AddMagicDebuff(Value, Type);
		break;
	case EMagicDebuffType::EMDT_StrengthBuff:
		StatsComponent->AddMagicDebuff(Value, Type);
		break;
	case EMagicDebuffType::EMDT_DefenseBuff:
		StatsComponent->AddMagicDebuff(Value, Type);
		break;
	case EMagicDebuffType::EMDT_AgilityBuff:
		StatsComponent->AddMagicDebuff(Value, Type);
		break;
	case EMagicDebuffType::EMDT_IntelligenceBuff:
		StatsComponent->AddMagicDebuff(Value, Type);
		break;
	case EMagicDebuffType::EMDT_StaminaBuff:
		StatsComponent->AddMagicDebuff(Value, Type);
		break;
	default:
		break;
	}
}

void ACharacterBase::ApplyDamage(float Damage)
{
	//TakeDamage(Damage, )
}

void ACharacterBase::MoveForward(float Value)
{
		bMovingForward = false;
		if ((Controller != nullptr) && (Value != 0.0f) && !bAttacking)
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
			bMovingForward = true;
		}

}

void ACharacterBase::MoveRight(float Value)
{
		bMovingRight = false;
		if ((Controller != nullptr) && (Value != 0.0f) && !bAttacking)
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
			bMovingRight = true;
		}
	

}

float ACharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	/**
	if (CharacterStats.Health - DamageAmount <= 0.f)
	{
		CharacterStats.Health = 0.f;
		Die();
		//if (DamageCauser)
		//{
		//	AEnemyBase* Enemy = Cast<AEnemyBase>(DamageCauser);
		//	if (Enemy)
		//	{
		//		Enemy->bHasValidTarget = false;
		//	}
		//}
	}
	else
	{
		CharacterStats.Health -= DamageAmount;
	}

	return DamageAmount;
	*/

	return 0.f;
}


void ACharacterBase::Die()
{

}

bool ACharacterBase::IsDead()
{
	return GetMovementStatus() != EMovementStatus::EMS_Dead;
}

void ACharacterBase::FollowPrimaryCharacter()
{
	URPGGameInstance* GI = Cast<URPGGameInstance>(UGameplayStatics::GetGameInstance(this));
	UPartySystem* PartySystem = Cast<UPartySystem>(GI->Party->GetDefaultObject());
	check(PartySystem);
	AIController->MoveToActor(PartySystem->GetPrimaryPartyMember(),15.f);
}
