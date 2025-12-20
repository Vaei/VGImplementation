// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VGImplementation : ModuleRules
{
	public VGImplementation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Vigil",
				"Grasp",
				"GameplayTags",
				"GameplayAbilities",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
			}
			);
	}
}
