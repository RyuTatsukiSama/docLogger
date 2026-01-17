// Copyright Epic Games, Inc. All Rights Reserved.

#include "docLoggerIntegrationGameMode.h"
#include "docLoggerIntegrationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AdocLoggerIntegrationGameMode::AdocLoggerIntegrationGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
