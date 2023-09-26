#include "MenuTool.h"
#include "RPGBuilder.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "KismetCompilerModule.h"
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 2
#include "AssetRegistry/AssetRegistryModule.h"
#include "Styling/AppStyle.h"
#else
#include "AssetRegistry/AssetRegistryModule.h"
#endif
#include "AssetToolsModule.h"
#include "ObjectTools.h"



#define LOCTEXT_NAMESPACE "MenuTool"

class MenuToolCommands : public TCommands<MenuToolCommands>
{
public:

	MenuToolCommands()
		: TCommands<MenuToolCommands>(
			TEXT("MenuTool"), // Context name for fast Lookup
			FText::FromString("Exmaple Menu tool"), // Context name for displaying
			NAME_None, // No parent context
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 2
			FAppStyle::GetAppStyleSetName() // UE5.2 and onward
#else
			FEditorStyle::GetStyleSetName() // Icon Style Set UE5.1 and previous
#endif
		)
	{

	}

	virtual void RegisterCommands() override
	{
		UI_COMMAND(MenuCommand1, "Create Game Instance Blueprint", "Creates a Game Instance blueprint that inherits from our custom Game Instance class.", EUserInterfaceActionType::Button, FInputGesture());
		UI_COMMAND(MenuCommand2, "Create Party System Blueprint", "Creates a Party System Blueprint from UPartySystem class.", EUserInterfaceActionType::Button, FInputGesture());
		UI_COMMAND(MenuCommand3, "Create Item Blueprint", "Creates an Item Blueprint from our UItemBase class.", EUserInterfaceActionType::Button, FInputGesture());
		
	}

public:
	
	TSharedPtr<FUICommandInfo> MenuCommand1; // Create GameInstance Child Blueprint
	TSharedPtr<FUICommandInfo> MenuCommand2; // Create Party System Blueprint
	TSharedPtr<FUICommandInfo> MenuCommand3; // Create Item Blueprint
};


void MenuTool::OnStartupModule()
{
	CommandList = MakeShareable(new FUICommandList);
	MenuToolCommands::Register();
	MapCommands();
	FRPGBuilderModule::Get().AddMenuExtension(
		FMenuExtensionDelegate::CreateRaw(this, &MenuTool::MakeMenuEntry),
		FName("Object Classes"),
		CommandList);
	
}
void MenuTool::OnShutdownModule()
{
	MenuToolCommands::Unregister();
}

void MenuTool::MakeMenuEntry(FMenuBuilder& MenuBuilder)
{

	MenuBuilder.AddSubMenu(
		FText::FromString("Object Classes"),
		FText::FromString("Object Classes sub menu"),
		FNewMenuDelegate::CreateSP(this, &MenuTool::MakeSubMenu)
	);
	
}

void MenuTool::MapCommands()
{
	const auto& Commands = MenuToolCommands::Get();

	CommandList->MapAction(
		Commands.MenuCommand1,
		FExecuteAction::CreateSP(this, &MenuTool::MenuCommand1),
		FCanExecuteAction());
	CommandList->MapAction(
		Commands.MenuCommand2,
		FExecuteAction::CreateSP(this, &MenuTool::MenuCommand2),
		FCanExecuteAction());
	CommandList->MapAction(
		Commands.MenuCommand3,
		FExecuteAction::CreateSP(this, &MenuTool::MenuCommand3),
		FCanExecuteAction());
}

void MenuTool::MenuCommand1() //Game Instance
{
	FGameProjectGenerationModule& GameProjectGenerationModule = FModuleManager::GetModuleChecked<FGameProjectGenerationModule>("GameProjectGeneration");
	FAddToProjectConfig ProjectConfig;
	const UClass* BlueprintClass = URPGGameInstance::StaticClass();
	ProjectConfig.ParentClass(BlueprintClass);
	ProjectConfig.WindowTitle(FText::FromString(TEXT("Create Game Instnace")));
	ProjectConfig.Modal();
	GameProjectGenerationModule.OpenAddBlueprintToProjectDialog(ProjectConfig);

	UE_LOG(LogClass, Log, TEXT("Game Instance Blueprint Created"));

	//TODO: Add switch to log returned Enum
}

void MenuTool::MenuCommand2() // Party
{
	FGameProjectGenerationModule& GameProjectGenerationModule = FModuleManager::GetModuleChecked<FGameProjectGenerationModule>("GameProjectGeneration");
	FAddToProjectConfig ProjectConfig;
	const UClass* BlueprintClass = UPartySystem::StaticClass();
	ProjectConfig.ParentClass(BlueprintClass);
	ProjectConfig.WindowTitle(FText::FromString(TEXT("Create Party System")));
	ProjectConfig.Modal();
	GameProjectGenerationModule.OpenAddBlueprintToProjectDialog(ProjectConfig);

	UE_LOG(LogClass, Log, TEXT("Party System Blueprint Created"));
}

void MenuTool::MenuCommand3() // Item
{
	FGameProjectGenerationModule& GameProjectGenerationModule = FModuleManager::GetModuleChecked<FGameProjectGenerationModule>("GameProjectGeneration");
	FAddToProjectConfig ProjectConfig;
	const UClass* BlueprintClass = UItemBase::StaticClass();
	ProjectConfig.ParentClass(BlueprintClass);
	ProjectConfig.WindowTitle(FText::FromString(TEXT("Item Blueprint Instance")));
	ProjectConfig.Modal();
	GameProjectGenerationModule.OpenAddBlueprintToProjectDialog(ProjectConfig);

	UE_LOG(LogClass, Log, TEXT("Item Blueprint Created"));
}

void MenuTool::MakeSubMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(MenuToolCommands::Get().MenuCommand1);
	MenuBuilder.AddMenuEntry(MenuToolCommands::Get().MenuCommand2);
	MenuBuilder.AddMenuEntry(MenuToolCommands::Get().MenuCommand3);
}
#undef LOCTEXT_NAMESPACE