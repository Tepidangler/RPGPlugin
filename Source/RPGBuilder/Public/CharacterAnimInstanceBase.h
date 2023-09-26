// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class RPGBUILDER_API UCharacterAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		float YawDelta;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		FRotator RotationLastTick;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		class ACharacterBase* MC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float Roll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float Yaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
		float TargetRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool bIsAccelerating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool bIsFullBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool bIsWeaponEquipped;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage | Section Names", meta =(ToolTip = "Use this array to add the names of the Sections that have the attack recovery animations in the combat montage"))
		TArray<FName> AttackRecoverySections;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage | Section Names",meta =(ToolTip = "Use this array to add the names of the sections of the attack animations in the combat montage "))
		TArray<FName> MontageSections;
	//Functions
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
		void UpdateAnimationProperties();
	
};
