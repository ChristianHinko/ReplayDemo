// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "RDGameInstance.generated.h"



/**
 * Base Game Instance.
 * Comes with instant replay functionality
 */
UCLASS()
class REPLAYDEMO_API URDGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	URDGameInstance(const FObjectInitializer& ObjectInitializer);


	// Instant replay constants
	static const FString InstantReplayName;
	static const FString InstantReplayFriendlyName;

	/** Play the instant replay */
	void PlayInstantReplay();
	/** Stop playing instant replay */
	void StopInstantReplay();

	/** Check if the instant replay is currently playing */
	bool IsPlayingInstantReplay() const;

protected:
	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;
#if WITH_EDITOR
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
#endif // WITH_EDITOR

};
