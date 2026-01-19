// Copyright Epic Games, Inc. All Rights Reserved.

#include "EM_TestEditorModeCommands.h"
#include "EM_TestEditorMode.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "EM_TestEditorModeCommands"

FEM_TestEditorModeCommands::FEM_TestEditorModeCommands()
	: TCommands<FEM_TestEditorModeCommands>("EM_TestEditorMode",
		NSLOCTEXT("EM_TestEditorMode", "EM_TestEditorModeCommands", "EM_Test Editor Mode"),
		NAME_None,
		FAppStyle::GetAppStyleSetName())
{
}

void FEM_TestEditorModeCommands::RegisterCommands()
{
	TArray <TSharedPtr<FUICommandInfo>>& ToolCommands = Commands.FindOrAdd(NAME_Default);

	UI_COMMAND(SimpleTool, "Show Actor Info", "Opens message box with info about a clicked actor", EUserInterfaceActionType::Button, FInputChord());
	ToolCommands.Add(SimpleTool);

	UI_COMMAND(InteractiveTool, "Measure Distance", "Measures distance between 2 points (click to set origin, shift-click to set end point)", EUserInterfaceActionType::ToggleButton, FInputChord());
	ToolCommands.Add(InteractiveTool);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> FEM_TestEditorModeCommands::GetCommands()
{
	return FEM_TestEditorModeCommands::Get().Commands;
}

#undef LOCTEXT_NAMESPACE
