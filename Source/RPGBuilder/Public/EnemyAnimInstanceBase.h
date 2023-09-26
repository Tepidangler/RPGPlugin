// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class RPGBUILDER_API UEnemyAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
	
public: //Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		class AEnemyBase* Enemy;



public: //Functions
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
		void UpdateAnimationProperties();

};
