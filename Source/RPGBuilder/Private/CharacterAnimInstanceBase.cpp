// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstanceBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterBase.h"
#include "Kismet/KismetMathLibrary.h"

void UCharacterAnimInstanceBase::NativeInitializeAnimation()
{
	//Check to see if Pawn is nullpointer
	if (Pawn == nullptr)
	{
		//Sets Pawn to PawnOwner if it can
		Pawn = TryGetPawnOwner();
	}

}

void UCharacterAnimInstanceBase::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			MC = Cast<ACharacterBase>(Pawn);
		}
	}

	if (Pawn)
	{
		UWorld* World = GetWorld();
		//Set Speed
		FVector Velocity = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Velocity.X, Velocity.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();

		//Set bIsInAir
		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

		//Set Roll, Pitch, and Yaw
		FRotator AimRotation = Pawn->GetBaseAimRotation();
		FRotator ActorRotation = Pawn->GetActorRotation();
		Roll = UKismetMathLibrary::NormalizedDeltaRotator(AimRotation, ActorRotation).Roll;
		Pitch = UKismetMathLibrary::NormalizedDeltaRotator(AimRotation, ActorRotation).Pitch;
		Yaw = UKismetMathLibrary::NormalizedDeltaRotator(AimRotation, ActorRotation).Yaw;

		//Set Yaw Delta
		RotationLastTick = Pawn->GetActorRotation();
		TargetRotation = (UKismetMathLibrary::NormalizedDeltaRotator(RotationLastTick, ActorRotation).Yaw / World->GetDeltaSeconds()) / 10;
		YawDelta = FMath::FInterpTo(YawDelta, TargetRotation, World->GetDeltaSeconds(), 6.f);

		//Set bisFullBody
		float CurveValue = GetCurveValue("FullBody");
		if (CurveValue > 0)
		{
			bIsFullBody = true;
		}


		if (Pawn)
		{
			MC = Cast<ACharacterBase>(Pawn);

			//Set Acceleration boolean
			if (MC)
			{
				float CurrentAcceleration = MC->GetCharacterMovement()->GetCurrentAcceleration().Size();
				if (CurrentAcceleration > 0)
				{
					bIsAccelerating = true;
				}
				else
				{
					bIsAccelerating = false;
				}

				if (MC->CharacterEquipment.LeftWeaponSlot || MC->CharacterEquipment.RightWeaponSlot)
				{
					bIsWeaponEquipped = true;
				}

				if (!MC->CharacterEquipment.LeftWeaponSlot && !MC->CharacterEquipment.RightWeaponSlot)
				{
					bIsWeaponEquipped = false;
				}

	
			}
			
		}
	}
}
