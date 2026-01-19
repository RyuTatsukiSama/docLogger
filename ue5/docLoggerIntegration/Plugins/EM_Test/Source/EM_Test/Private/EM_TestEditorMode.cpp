// Copyright Epic Games, Inc. All Rights Reserved.

#include "EM_TestEditorMode.h"
#include "EM_TestEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "EM_TestEditorModeCommands.h"


//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
// AddYourTool Step 1 - include the header file for your Tools here
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
#include "Tools/EM_TestSimpleTool.h"
#include "Tools/EM_TestInteractiveTool.h"

// step 2: register a ToolBuilder in FEM_TestEditorMode::Enter() below


#define LOCTEXT_NAMESPACE "EM_TestEditorMode"

const FEditorModeID UEM_TestEditorMode::EM_EM_TestEditorModeId = TEXT("EM_EM_TestEditorMode");

FString UEM_TestEditorMode::SimpleToolName = TEXT("EM_Test_ActorInfoTool");
FString UEM_TestEditorMode::InteractiveToolName = TEXT("EM_Test_MeasureDistanceTool");


UEM_TestEditorMode::UEM_TestEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(UEM_TestEditorMode::EM_EM_TestEditorModeId,
		LOCTEXT("ModeName", "EM_Test"),
		FSlateIcon(),
		true);
}


UEM_TestEditorMode::~UEM_TestEditorMode()
{
}


void UEM_TestEditorMode::ActorSelectionChangeNotify()
{
}

void UEM_TestEditorMode::Enter()
{
	UEdMode::Enter();

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// AddYourTool Step 2 - register the ToolBuilders for your Tools here.
	// The string name you pass to the ToolManager is used to select/activate your ToolBuilder later.
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////// 
	const FEM_TestEditorModeCommands& SampleToolCommands = FEM_TestEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.SimpleTool, SimpleToolName, NewObject<UEM_TestSimpleToolBuilder>(this));
	RegisterTool(SampleToolCommands.InteractiveTool, InteractiveToolName, NewObject<UEM_TestInteractiveToolBuilder>(this));

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, SimpleToolName);
}

void UEM_TestEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FEM_TestEditorModeToolkit);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UEM_TestEditorMode::GetModeCommands() const
{
	return FEM_TestEditorModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE
