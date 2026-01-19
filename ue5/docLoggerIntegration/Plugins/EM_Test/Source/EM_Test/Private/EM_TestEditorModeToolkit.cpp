// Copyright Epic Games, Inc. All Rights Reserved.

#include "EM_TestEditorModeToolkit.h"
#include "EM_TestEditorMode.h"
#include "Engine/Selection.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "EM_TestEditorModeToolkit"

FEM_TestEditorModeToolkit::FEM_TestEditorModeToolkit()
{
}

void FEM_TestEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);
}

void FEM_TestEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}


FName FEM_TestEditorModeToolkit::GetToolkitFName() const
{
	return FName("EM_TestEditorMode");
}

FText FEM_TestEditorModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("DisplayName", "EM_TestEditorMode Toolkit");
}

#undef LOCTEXT_NAMESPACE
