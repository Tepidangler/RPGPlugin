// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PartySystem.h"
#include "RPGGameInstance.generated.h"

/**
 * 
 */

class UPartySystem;

UCLASS()
class RPGBUILDER_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	URPGGameInstance();

protected:
	virtual void Init() override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Party System")
	TSubclassOf<UPartySystem> Party;
};
