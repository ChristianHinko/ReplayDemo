// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "RDPlayerController.generated.h"


class URDGameInstance;



/**
 * Base Player Controller.
 * Handles input for instant replays
 */
UCLASS()
class REPLAYDEMO_API ARDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARDPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void ToggleInstantReplay();

	// Cached Game Instance
	URDGameInstance* RDGameInstance;

};
