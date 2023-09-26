// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RPGBuilder : ModuleRules
{
	public RPGBuilder(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange( new string[]
			{
				"Core",
                "Engine",
                "CoreUObject",
                "InputCore",
                "LevelEditor",
                "Slate",
				"SlateCore",
				"UMG",
                "GameProjectGeneration",
                "AssetTools",
                "UnrealEd",
				"EditorStyle",
				"DataRegistry",
				"AIModule"

			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "AppFramework",
                "GameProjectGeneration",
                "AnimGraph",
                "UnrealEd",
                "KismetWidgets",
                "DesktopWidgets",
                "MainFrame",
                "PropertyEditor",
                "ComponentVisualizers",

				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
