// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGSScalableFloat.h"
#include "Components/ActorComponent.h"
#include "ItemBase.h"
#include "MagicBase.h"
#include "StatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGBUILDER_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

	//These Represent The max values at any given level
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FAGSScalableFloat Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FAGSScalableFloat MagicPoints;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FAGSScalableFloat Strength;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FAGSScalableFloat MagicAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FAGSScalableFloat Agility;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FAGSScalableFloat Defense;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FAGSScalableFloat MagicDefense;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FAGSScalableFloat Intelligence;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FAGSScalableFloat Stamina;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FAGSScalableFloat XPToNextLevel;

	//Represents values in current state
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float Level = 1.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	float CurrentXP = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	float CurrentHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	float CurrentMP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	float CurrentStamina;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddXP(float XP);
	//Uses Multiplication rather than addition
	void AddMagicBuff(float Value, EMagicBuffType Type);

	void AddMagicDebuff(float Value, EMagicDebuffType Type);

	//Uses Addition rather than multiplication
	void AddItemBuff(float Value, EItemBuffType Type);

	void AddItemDebuff(float Value, EItemDebuffType Type);

		
};
