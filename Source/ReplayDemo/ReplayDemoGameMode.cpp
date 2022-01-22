// Copyright Epic Games, Inc. All Rights Reserved.

#include "ReplayDemoGameMode.h"
#include "ReplayDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AReplayDemoGameMode::AReplayDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
