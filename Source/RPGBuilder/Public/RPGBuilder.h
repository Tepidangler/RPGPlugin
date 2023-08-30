// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AGSScalableFloat.h"
#include "ArmorBase.h"
#include "CharacterBase.h"
#include "Interactables.h"
#include "InventoryComponent.h"
#include "ItemBase.h"
#include "StatsComponent.h"
#include "WeaponBase.h"
#include "MagicBase.h"
#include "AbilityBase.h"
#include "ASComponent.h"
#include "MagicSystemComponent.h"

class FRPGBuilderModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
