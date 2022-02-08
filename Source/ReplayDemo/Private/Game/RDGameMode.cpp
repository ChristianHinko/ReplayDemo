// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/RDGameMode.h"

#include "Game/RDGameState.h"
#include "Player/RDPlayerController.h"
#include "Character/RDCharacter.h"
#include "Character/RDSpectatorPawn.h"



ARDGameMode::ARDGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = ARDGameState::StaticClass();

	PlayerControllerClass = ARDPlayerController::StaticClass();
	ReplaySpectatorPlayerControllerClass = ARDPlayerController::StaticClass();

	DefaultPawnClass = ARDCharacter::StaticClass();
	SpectatorClass = ARDSpectatorPawn::StaticClass();

}
