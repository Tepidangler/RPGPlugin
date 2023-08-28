#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Particles/ParticleSystemComponent.h"
#include "AbilityBase.generated.h"

UCLASS()
class RPGBUILDER_API UAbilityBase : public UObject
{
	GENERATED_BODY()
public:
	UAbilityBase();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particles")
	UParticleSystemComponent* ParticleSystemComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo")
	FName Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo")
	float Cost;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo")
	float CastTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo")
	float Attack;
};

