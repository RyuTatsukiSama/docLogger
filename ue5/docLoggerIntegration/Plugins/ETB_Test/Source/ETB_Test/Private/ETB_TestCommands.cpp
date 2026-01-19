// Copyright Epic Games, Inc. All Rights Reserved.

#include "ETB_TestCommands.h"

#define LOCTEXT_NAMESPACE "FETB_TestModule"

void FETB_TestCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "ETB_Test", "Execute ETB_Test action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
