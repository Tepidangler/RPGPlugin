// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RPGBUILDER_API ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//Variables

	/**Reference to the UMG Asset in the editor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> HUDOverlayAsset;

	/**Variable to hold the Widget after creating it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		UUserWidget* HUDOverlay;


protected:

	virtual void BeginPlay() override;

public: //Functions
	
};
