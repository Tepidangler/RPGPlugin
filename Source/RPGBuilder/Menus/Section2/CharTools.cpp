#include "CharTools.h"
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


#define LOCTEXT_NAMESPACE "CharTools"

class CharToolCommands : public TCommands<CharToolCommands>
{
public:

	CharToolCommands()
		: TCommands<CharToolCommands>(
			TEXT("CharTool"), // Context name for fast Lookup
			FText::FromString("Exmaple Char tool"), // Context name for displaying
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
		UI_COMMAND(MenuCommand1, "Create Character Blueprint", "Creates a non-enemy character using our custom Character Class.", EUserInterfaceActionType::Button, FInputGesture());
		UI_COMMAND(MenuCommand2, "Create Enemy Blueprint", "Creates an enemy character using our custom Enemy Class.", EUserInterfaceActionType::Button, FInputGesture());
		UI_COMMAND(MenuCommand3, "Create Weapon Blueprint", "Creates a Weapon Blueprint using our custom Weapon Base Class", EUserInterfaceActionType::Button, FInputGesture());
		UI_COMMAND(MenuCommand4, "Create Armor Blueprint", "Creates an Armor Blueprint using our custom Armor Base Class", EUserInterfaceActionType::Button, FInputGesture());
		UI_COMMAND(MenuCommand5, "Create Ability Blueprint", "Creates an Ability Blueprint using our custom Ability Base Class", EUserInterfaceActionType::Button, FInputGesture());
		UI_COMMAND(MenuCommand6, "Create Magic Blueprint", "Creates a Magic Blueprint using our custom Magic Base Class", EUserInterfaceActionType::Button, FInputGesture());
		UI_COMMAND(MenuCommand7, "Create Interactable Blueprint", "Creates an Interactable Bluepring using our custom Interactables class", EUserInterfaceActionType::Button, FInputGesture());
		UI_COMMAND(MenuCommand8, "Create Player Controller Blueprin", "Creates a Custom Player Controller", EUserInterfaceActionType::Button, FInputGesture());

	}

public:

	TSharedPtr<FUICommandInfo> MenuCommand1; // Create CharacterBase Child Blueprint
	TSharedPtr<FUICommandInfo> MenuCommand2; // Create EnemyBase ChildBlueprint
	TSharedPtr<FUICommandInfo> MenuCommand3; // Create WeaponBase Child Blueprint
	TSharedPtr<FUICommandInfo> MenuCommand4; // Create ArmorBase Child Blueprint
	TSharedPtr<FUICommandInfo> MenuCommand5; // Create Ability Child Blueprint 
	TSharedPtr<FUICommandInfo> MenuCommand6; // Create Magic Child Blueprint
	TSharedPtr<FUICommandInfo> MenuCommand7; // Create Interactable Blueprint
	TSharedPtr<FUICommandInfo> MenuCommand8; // Create Player Controller Blueprint
};


void CharTools::OnStartupModule()
{
	CommandList = MakeShareable(new FUICommandList);
	CharToolCommands::Register();
	MapCommands();
	FRPGBuilderModule::Get().AddMenuExtension(
		FMenuExtensionDelegate::CreateRaw(this, &CharTools::MakeMenuEntry),
		FName("Actor Classes"),
		CommandList);

}
void CharTools::OnShutdownModule()
{
	CharToolCommands::Unregister();
}

void CharTools::MakeMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddSubMenu(
		FText::FromString("Actor Classes"),
		FText::FromString("Actor  Classes sub menu"),
		FNewMenuDelegate::CreateSP(this, &CharTools::MakeSubMenu)
	);
}

void CharTools::MapCommands()
{
	const auto& Commands = CharToolCommands::Get();

	CommandList->MapAction(
		Commands.MenuCommand1,
		FExecuteAction::CreateSP(this, &CharTools::MenuCommand1),
		FCanExecuteAction());
	CommandList->MapAction(
		Commands.MenuCommand2,
		FExecuteAction::CreateSP(this, &CharTools::MenuCommand2),
		FCanExecuteAction());
	CommandList->MapAction(
		Commands.MenuCommand3,
		FExecuteAction::CreateSP(this, &CharTools::MenuCommand3),
		FCanExecuteAction());
	CommandList->MapAction(
		Commands.MenuCommand4,
		FExecuteAction::CreateSP(this, &CharTools::MenuCommand4),
		FCanExecuteAction());
	CommandList->MapAction(
		Commands.MenuCommand5,
		FExecuteAction::CreateSP(this, &CharTools::MenuCommand5),
		FCanExecuteAction());
	CommandList->MapAction(
		Commands.MenuCommand6,
		FExecuteAction::CreateSP(this, &CharTools::MenuCommand6),
		FCanExecuteAction());
	CommandList->MapAction(
		Commands.MenuCommand7,
		FExecuteAction::CreateSP(this, &CharTools::MenuCommand7),
		FCanExecuteAction());
	CommandList->MapAction(
		Commands.MenuCommand8,
		FExecuteAction::CreateSP(this, &CharTools::MenuCommand8),
		FCanExecuteAction());

}

void CharTools::MenuCommand1() // Character
{
	FGameProjectGenerationModule& GameProjectGenerationModule = FModuleManager::GetModuleChecked<FGameProjectGenerationModule>("GameProjectGeneration");
	FAddToProjectConfig ProjectConfig;
	const UClass* BlueprintClass = ACharacterBase::StaticClass();
	ProjectConfig.ParentClass(BlueprintClass);
	ProjectConfig.WindowTitle(FText::FromString(TEXT("Character Blueprint Instance")));
	ProjectConfig.Modal();
	GameProjectGenerationModule.OpenAddBlueprintToProjectDialog(ProjectConfig);

	//TODO: Add switch to log returned Enum
	UE_LOG(LogClass, Log, TEXT("Character Blueprint Created"));
}

void CharTools::MenuCommand2() // Enemy
{
	FGameProjectGenerationModule& GameProjectGenerationModule = FModuleManager::GetModuleChecked<FGameProjectGenerationModule>("GameProjectGeneration");
	FAddToProjectConfig ProjectConfig;
	const UClass* BlueprintClass = AEnemyBase::StaticClass();
	ProjectConfig.ParentClass(BlueprintClass);
	ProjectConfig.WindowTitle(FText::FromString(TEXT("Enemy Blueprint Instance")));
	ProjectConfig.Modal();
	GameProjectGenerationModule.OpenAddBlueprintToProjectDialog(ProjectConfig);

	//TODO: Add switch to log returned Enum
	UE_LOG(LogClass, Log, TEXT("Enemy Blueprint Created"));
}
void CharTools::MenuCommand3() // Weapon
{
	FGameProjectGenerationModule& GameProjectGenerationModule = FModuleManager::GetModuleChecked<FGameProjectGenerationModule>("GameProjectGeneration");
	FAddToProjectConfig ProjectConfig;
	const UClass* BlueprintClass = AWeaponBase::StaticClass();
	ProjectConfig.ParentClass(BlueprintClass);
	ProjectConfig.WindowTitle(FText::FromString(TEXT("Weapon Blueprint Instance")));
	ProjectConfig.Modal();
	GameProjectGenerationModule.OpenAddBlueprintToProjectDialog(ProjectConfig);

	//TODO: Add switch to log returned Enum
	UE_LOG(LogClass, Log, TEXT("Weapon Blueprint Created"));
}

void CharTools::MenuCommand4() //Armor
{
	FGameProjectGenerationModule& GameProjectGenerationModule = FModuleManager::GetModuleChecked<FGameProjectGenerationModule>("GameProjectGeneration");
	FAddToProjectConfig ProjectConfig;
	const UClass* BlueprintClass = AArmorBase::StaticClass();
	ProjectConfig.ParentClass(BlueprintClass);
	ProjectConfig.WindowTitle(FText::FromString(TEXT("Armor Blueprint Instance")));
	ProjectConfig.Modal();
	GameProjectGenerationModule.OpenAddBlueprintToProjectDialog(ProjectConfig);

	//TODO: Add switch to log returned Enum
	UE_LOG(LogClass, Log, TEXT("Armor Blueprint Created"));
}

void CharTools::MenuCommand5() //Ability
{
	FGameProjectGenerationModule& GameProjectGenerationModule = FModuleManager::GetModuleChecked<FGameProjectGenerationModule>("GameProjectGeneration");
	FAddToProjectConfig ProjectConfig;
	const UClass* BlueprintClass = AAbilityBase::StaticClass();
	ProjectConfig.ParentClass(BlueprintClass);
	ProjectConfig.WindowTitle(FText::FromString(TEXT("Abilty Blueprint Instance")));
	ProjectConfig.Modal();
	GameProjectGenerationModule.OpenAddBlueprintToProjectDialog(ProjectConfig);

	//TODO: Add switch to log returned Enum
	UE_LOG(LogClass, Log, TEXT("Ability Blueprint Created"));
}

void CharTools::MenuCommand6() // Magic
{
	FGameProjectGenerationModule& GameProjectGenerationModule = FModuleManager::GetModuleChecked<FGameProjectGenerationModule>("GameProjectGeneration");
	FAddToProjectConfig ProjectConfig;
	const UClass* BlueprintClass = AMagicBase::StaticClass();
	ProjectConfig.ParentClass(BlueprintClass);
	ProjectConfig.WindowTitle(FText::FromString(TEXT("Magic Blueprint Instance")));
	ProjectConfig.Modal();
	GameProjectGenerationModule.OpenAddBlueprintToProjectDialog(ProjectConfig);

	//TODO: Add switch to log returned Enum
	UE_LOG(LogClass, Log, TEXT("Magic Blueprint Created"));
}

void CharTools::MenuCommand7() // Interactable
{
	FGameProjectGenerationModule& GameProjectGenerationModule = FModuleManager::GetModuleChecked<FGameProjectGenerationModule>("GameProjectGeneration");
	FAddToProjectConfig ProjectConfig;
	const UClass* BlueprintClass = AInteractables::StaticClass();
	ProjectConfig.ParentClass(BlueprintClass);
	ProjectConfig.WindowTitle(FText::FromString(TEXT("Interactable Blueprint Instance")));
	ProjectConfig.Modal();
	GameProjectGenerationModule.OpenAddBlueprintToProjectDialog(ProjectConfig);
	UE_LOG(LogClass, Log, TEXT("Interactable Blueprint Created"));
}

void CharTools::MenuCommand8() // Player Controller
{
	FGameProjectGenerationModule& GameProjectGenerationModule = FModuleManager::GetModuleChecked<FGameProjectGenerationModule>("GameProjectGeneration");
	FAddToProjectConfig ProjectConfig;
	const UClass* BlueprintClass = ARPGPlayerController::StaticClass();
	ProjectConfig.ParentClass(BlueprintClass);
	ProjectConfig.WindowTitle(FText::FromString(TEXT("PlayerController Blueprint Instance")));
	ProjectConfig.Modal();
	GameProjectGenerationModule.OpenAddBlueprintToProjectDialog(ProjectConfig);
	UE_LOG(LogClass, Log, TEXT("Player Controller Blueprint Created"));
}


void CharTools::MakeSubMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(CharToolCommands::Get().MenuCommand1);
	MenuBuilder.AddMenuEntry(CharToolCommands::Get().MenuCommand2);
	MenuBuilder.AddMenuEntry(CharToolCommands::Get().MenuCommand3);
	MenuBuilder.AddMenuEntry(CharToolCommands::Get().MenuCommand4);
	MenuBuilder.AddMenuEntry(CharToolCommands::Get().MenuCommand5);
	MenuBuilder.AddMenuEntry(CharToolCommands::Get().MenuCommand6);
	MenuBuilder.AddMenuEntry(CharToolCommands::Get().MenuCommand7);
	MenuBuilder.AddMenuEntry(CharToolCommands::Get().MenuCommand8);
}
#undef LOCTEXT_NAMESPACE