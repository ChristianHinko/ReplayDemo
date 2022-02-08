// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RDPlayerController.h"

#include "Game/RDGameInstance.h"



ARDPlayerController::ARDPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void ARDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	RDGameInstance = GetGameInstance<URDGameInstance>();
}


void ARDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	InputComponent->BindAction(FName(TEXT("InstantReplay")), IE_Pressed, this, &ARDPlayerController::ToggleInstantReplay);

}

void ARDPlayerController::ToggleInstantReplay()
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
