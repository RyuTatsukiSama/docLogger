// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ETB_TestStyle.h"

class FETB_TestCommands : public TCommands<FETB_TestCommands>
{
public:

	FETB_TestCommands()
		: TCommands<FETB_TestCommands>(TEXT("ETB_Test"), NSLOCTEXT("Contexts", "ETB_Test", "ETB_Test Plugin"), NAME_None, FETB_TestStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
