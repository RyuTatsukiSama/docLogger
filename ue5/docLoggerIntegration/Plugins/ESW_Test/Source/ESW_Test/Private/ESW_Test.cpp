// Copyright Epic Games, Inc. All Rights Reserved.

#include "ESW_Test.h"
#include "ESW_TestStyle.h"
#include "ESW_TestCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName ESW_TestTabName("ESW_Test");

#define LOCTEXT_NAMESPACE "FESW_TestModule"

void FESW_TestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FESW_TestStyle::Initialize();
	FESW_TestStyle::ReloadTextures();

	FESW_TestCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FESW_TestCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FESW_TestModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FESW_TestModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ESW_TestTabName, FOnSpawnTab::CreateRaw(this, &FESW_TestModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FESW_TestTabTitle", "ESW_Test"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FESW_TestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FESW_TestStyle::Shutdown();

	FESW_TestCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ESW_TestTabName);
}

TSharedRef<SDockTab> FESW_TestModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FESW_TestModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("ESW_Test.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FESW_TestModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(ESW_TestTabName);
}

void FESW_TestModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FESW_TestCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FESW_TestCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FESW_TestModule, ESW_Test)