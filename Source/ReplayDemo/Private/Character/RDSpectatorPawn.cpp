// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RDSpectatorPawn.h"

#include "Components/InputComponent.h"
#include "Game/RDGameInstance.h"



ARDSpectatorPawn::ARDSpectatorPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void ARDSpectatorPawn::BeginPlay()
{
	Super::BeginPlay();

	RDGameInstance = GetGameInstance<URDGameInstance>();
}

void ARDSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// Action
	PlayerInputComponent->BindAction(FName(TEXT("InstantReplay")), IE_Pressed, this, &ARDSpectatorPawn::ToggleInstantReplay);

}


// Actions

void ARDSpectatorPawn::ToggleInstantReplay()
{
	if (RDGameInstance->IsPlayingInstantReplay())
	{
		// Stop playing instant replay
		RDGameInstance->StopInstantReplay();
		return;
	}

	// Play instant replay
	RDGameInstance->PlayInstantReplay();
}
