// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/RDGameInstance.h"

#include "Engine/DemoNetDriver.h"
#include "ReplaySubsystem.h"



// Instant replay constants
const FString URDGameInstance::InstantReplayName = TEXT("InstantReplay");
const FString URDGameInstance::InstantReplayFriendlyName = TEXT("Instant Replay");

URDGameInstance::URDGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void URDGameInstance::RecordInstantReplay()
{
	FJsonSerializableArray ReplayOptions;
	//ReplayOptions.Emplace(TEXT("ReplayStreamerOverride=InMemoryNetworkReplayStreaming"));

	StartRecordingReplay(InstantReplayName, InstantReplayFriendlyName, ReplayOptions);
}
void URDGameInstance::PlayInstantReplay()
{
	StopRecordingReplay();
	PlayReplay(InstantReplayName);
}
void URDGameInstance::StopInstantReplay()
{
	// TODO: UReplaySubsystem::bLoadDefaultMapOnStop feels broken because it
	// just calls the UEngine::Browse() function outta nowhere (which is a really sensitive function).
	// 
	// This ends up freezing the engine when calling StopRecordingReplay(). So for now we
	// are just going to ensure bLoadDefaultMapOnStop is false when we call it here.
	// 
	// Possible work-arounds:
	//		1) Load a Level manually via APlayerController::ClientTravel() or UWorld::ServerTravel()
	//		2) Override UEngine::TickWorldTravel() and call StopRecordingReplay() there
	//		3) Bind to the FCoreDelegates::OnBeginFrame delegate and call StopRecordingReplay() there
	//			- But be sure to construct an FScopedConditionalWorldSwitcher so that the Editor Engine doesn't break
	// 

	
	bool bLoadDefaultMapOnStop; // to keep track of the old value

	UReplaySubsystem* ReplaySubsystem = GetSubsystem<UReplaySubsystem>();
	if (IsValid(ReplaySubsystem))
	{
		bLoadDefaultMapOnStop = ReplaySubsystem->bLoadDefaultMapOnStop;
		ReplaySubsystem->bLoadDefaultMapOnStop = false;
	}

	// Stop the replay playback
	StopRecordingReplay();

	if (IsValid(ReplaySubsystem))
	{
		ReplaySubsystem->bLoadDefaultMapOnStop = bLoadDefaultMapOnStop;
	}

}

bool URDGameInstance::IsPlayingInstantReplay() const
{
	const UWorld* World = GetWorld();
	if (IsValid(World))
	{
		const UDemoNetDriver* DemoNetDriver = World->GetDemoNetDriver();
		if (IsValid(DemoNetDriver))
		{
			const FString& ActiveReplayName = DemoNetDriver->GetActiveReplayName();

			if (DemoNetDriver->IsPlaying() && ActiveReplayName == InstantReplayName)
			{
				// Instant Replay is playing!
				return true;
			}

		}
	}

	return false;
}
