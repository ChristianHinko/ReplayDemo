// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"

#include "RDSpectatorPawn.generated.h"


class URDGameInstance;



/**
 * 
 */
UCLASS()
class REPLAYDEMO_API ARDSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	ARDSpectatorPawn(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Actions
	void ToggleInstantReplay();


	// Cached Game Instance
	URDGameInstance* RDGameInstance;

};
