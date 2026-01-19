// Copyright Epic Games, Inc. All Rights Reserved.

#include "ESW_TestCommands.h"

#define LOCTEXT_NAMESPACE "FESW_TestModule"

void FESW_TestCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ESW_Test", "Bring up ESW_Test window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
