// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"

#include "RDGameState.generated.h"



/**
 * Base Game State.
 * Starts instant replay on match start
 */
UCLASS()
class REPLAYDEMO_API ARDGameState : public AGameState
{
	GENERATED_BODY()

public:
	ARDGameState(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void HandleMatchHasStarted();

};
