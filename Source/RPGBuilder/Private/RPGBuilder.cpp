// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGBuilder.h"
#include "RPGBuilderInterface.h"

#define LOCTEXT_NAMESPACE "FRPGBuilderModule"

TSharedRef<FWorkspaceItem> FRPGBuilderModule::MenuRoot = FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));

void FRPGBuilderModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (!IsRunningCommandlet())
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorMenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
		MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension("Window", EExtensionHook::After, NULL, FMenuBarExtensionDelegate::CreateRaw(this, &FRPGBuilderModule::MakePulldownMenu));
		LevelEditorMenuExtensibilityManager->AddExtender(MenuExtender);
	}
    IRPGBuilderModuleInterface::StartupModule();
}

void FRPGBuilderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    IRPGBuilderModuleInterface::ShutdownModule();
}

void FRPGBuilderModule::AddModuleListeners()
{
	ModuleListeners.Add(MakeShareable(new MenuTool));
	ModuleListeners.Add(MakeShareable(new CharTools));
	ModuleListeners.Add(MakeShareable(new ObjectEditorTool));
}

void FRPGBuilderModule::AddMenuExtension(const FMenuExtensionDelegate& extensionDelegate, FName extensionHook, const TSharedPtr<FUICommandList>& CommandList, EExtensionHook::Position Position)
{
	MenuExtender->AddMenuExtension(extensionHook, Position, CommandList, extensionDelegate);
}

void FRPGBuilderModule::MakePulldownMenu(FMenuBarBuilder& MenuBuilder)
{
	MenuBuilder.AddPullDownMenu(
		FText::FromString("RPGBuilder"),
		FText::FromString("Open the RPGBuilder Menu"),
		FNewMenuDelegate::CreateRaw(this, &FRPGBuilderModule::FillPulldownMenu),
		"RPGBuilder",
		FName(TEXT("RPGBuilder Menu"))
	);
}

void FRPGBuilderModule::FillPulldownMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("Objects", FText::FromString("Object Classes"));
	MenuBuilder.AddMenuSeparator(FName("Object Classes"));
	MenuBuilder.EndSection();

	MenuBuilder.BeginSection("Actor", FText::FromString("Actor Classes"));
	MenuBuilder.AddMenuSeparator("Actor Classes");
	MenuBuilder.EndSection();

	MenuBuilder.BeginSection("EditObjects", FText::FromString("Edit Objects"));
	MenuBuilder.AddMenuSeparator(FName("Edit Objects"));
	MenuBuilder.EndSection();


}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_GAME_MODULE(FRPGBuilderModule, RPGBuilder)