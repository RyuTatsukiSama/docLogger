// Copyright Epic Games, Inc. All Rights Reserved.

#include "BL_Test.h"

#define LOCTEXT_NAMESPACE "FBL_TestModule"

void FBL_TestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FBL_TestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBL_TestModule, BL_Test)