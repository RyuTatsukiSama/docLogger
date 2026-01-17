// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class docLoggerIntegration : ModuleRules
{
	public docLoggerIntegration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
