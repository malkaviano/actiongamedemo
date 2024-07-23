// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AGDemonstration : ModuleRules
{
	public AGDemonstration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput"
		});

		PublicIncludePaths.Add("AGDemonstration/");

		PrivateDependencyModuleNames.AddRange(new string [] {
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});
	}
}
