// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/RDGameState.h"

#include "Game/RDGameInstance.h"



ARDGameState::ARDGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void ARDGameState::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	//GetGameInstance<URDGameInstance>()->RecordInstantReplay();
}
