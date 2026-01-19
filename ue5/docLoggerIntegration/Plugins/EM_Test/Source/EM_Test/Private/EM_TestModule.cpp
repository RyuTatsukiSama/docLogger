// Copyright Epic Games, Inc. All Rights Reserved.

#include "EM_TestModule.h"
#include "EM_TestEditorModeCommands.h"

#define LOCTEXT_NAMESPACE "EM_TestModule"

void FEM_TestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FEM_TestEditorModeCommands::Register();
}

void FEM_TestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FEM_TestEditorModeCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEM_TestModule, EM_TestEditorMode)