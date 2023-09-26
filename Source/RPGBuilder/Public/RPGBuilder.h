// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnrealEd.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Editor/LevelEditor/Public/LevelEditor.h"
#include "Editor/PropertyEditor/Public/PropertyEditing.h"
#include "IAssetTypeActions.h"
#include "RPGBuilderInterface.h"
#include "AbilityBase.h"
#include "AGSScalableFloat.h"
#include "ArmorBase.h"
#include "ASComponent.h"
#include "CharacterBase.h"
#include "EnemyBase.h"
#include "Interactables.h"
#include "InventoryComponent.h"
#include "ItemBase.h"
#include "MagicBase.h"
#include "MagicSystemComponent.h"
#include "PartySystem.h"
#include "RPGGameInstance.h"
#include "RPGPlayerController.h"
#include "StatsComponent.h"
#include "WeaponBase.h"

class FRPGBuilderModule : public IRPGBuilderModuleInterface
{
public:

	/** IModuleInterface implementation */
    virtual void StartupModule() override;

    virtual void ShutdownModule() override;

    virtual void AddModuleListeners() override;

    static inline FRPGBuilderModule& Get()
    {
        return FModuleManager::LoadModuleChecked<FRPGBuilderModule>("RPGBuilder");
    }

    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("RPGBuilder");
    }

    void AddMenuExtension(const FMenuExtensionDelegate& extensionDelegate, FName extensionHook, const TSharedPtr<FUICommandList>& CommandList = NULL, EExtensionHook::Position Position = EExtensionHook::Before);

    TSharedRef<FWorkspaceItem> GetMenuRoot() { return FRPGBuilderModule::MenuRoot; }
    
 

protected:
    TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;
    TSharedPtr<FExtender> MenuExtender;

    static TSharedRef<FWorkspaceItem> MenuRoot;

    void MakePulldownMenu(FMenuBarBuilder& MenuBuilder);

    void FillPulldownMenu(FMenuBuilder& MenuBuilder);

};

