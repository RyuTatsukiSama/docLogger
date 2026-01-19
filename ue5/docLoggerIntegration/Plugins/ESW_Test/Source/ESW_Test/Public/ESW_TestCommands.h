// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ESW_TestStyle.h"

class FESW_TestCommands : public TCommands<FESW_TestCommands>
{
public:

	FESW_TestCommands()
		: TCommands<FESW_TestCommands>(TEXT("ESW_Test"), NSLOCTEXT("Contexts", "ESW_Test", "ESW_Test Plugin"), NAME_None, FESW_TestStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};