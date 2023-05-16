// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SymplLogin : ModuleRules
{
	public SymplLogin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
            }
			);


        PrivateIncludePaths.AddRange(
            new string[]
            {

			}
            );

        PublicDependencyModuleNames.AddRange(
			new string[] 
			{ 
				"Core", 
				"CoreUObject",
                "DeveloperSettings",
                "Engine", 
				"OnlineSubsystem", 
				"OnlineSubsystemUtils",
                "PlayFab", 
				"PlayFabCpp", 
				"PlayFabCommon",
				"Steamworks", 
				"OnlineSubsystem", 
				"OnlineSubsystemUtils", 
				"OnlineSubsystemSteam"
            }
			);

        // Add definitions for WITH_PLAYFAB and WITH_STEAMWORKS macros.
        PublicDefinitions.Add("WITH_PLAYFAB=1");
        PublicDefinitions.Add("WITH_STEAMWORKS=1");

        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"PlayFab", 
				"PlayFabCpp",
                "PlayFabCommon",
                "Steamworks",
                "OnlineSubsystem",
                "OnlineSubsystemUtils",
                "OnlineSubsystemSteam"	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        // Enable RTTI and exceptions for Steamworks.
        bEnableExceptions = true;
        bUseRTTI = true;

    }
}
