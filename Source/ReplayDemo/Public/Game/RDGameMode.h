// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "RDGameMode.generated.h"



/**
 * Base Game Mode
 */
UCLASS()
class REPLAYDEMO_API ARDGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ARDGameMode(const FObjectInitializer& ObjectInitializer);

protected:

};
