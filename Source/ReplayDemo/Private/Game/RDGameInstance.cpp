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
	// Configure our replay options
	InstantReplayReplayOptions.Emplace(TEXT("LocalFileNetworkReplayStreamer"));

}


void URDGameInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	Super::LoadComplete(LoadTime, MapName);

	// Start recording our instant replay
	if (GetWorld()->IsPlayingReplay() == false)
	{
		if (!IsRecordingInstantReplay())
		{
			StartRecordingReplay(InstantReplayName, InstantReplayFriendlyName, InstantReplayReplayOptions);
		}
	}
}

#if WITH_EDITOR
FGameInstancePIEResult URDGameInstance::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
{
	const FGameInstancePIEResult& RetVal = Super::StartPlayInEditorGameInstance(LocalPlayer, Params);

	// Start recording our instant replay
	if (GetWorld()->IsPlayingReplay() == false)
	{
		if (!IsRecordingInstantReplay())
		{
			StartRecordingReplay(InstantReplayName, InstantReplayFriendlyName, InstantReplayReplayOptions);
		}
	}
	
	return RetVal;
}
#endif // WITH_EDITOR


void URDGameInstance::PlayInstantReplay()
{
	// Stop recording
	StopRecordingReplay();

	// Save our URL before Traveling to the instant replay
	if (!IsPlayingInstantReplay())
	{
		PreInstantReplayURL = GetWorld()->URL;
	}

	// Play it
	PlayReplay(InstantReplayName);
}
void URDGameInstance::StopInstantReplay()
{
	// NOTE: UReplaySubsystem::bLoadDefaultMapOnStop feels broken because it
	// just calls the UEngine::Browse() function outta nowhere (which is a really sensitive function).
	// 
	// This ends up freezing the engine when calling StopRecordingReplay(). So for now we
	// are just going to ensure bLoadDefaultMapOnStop is false when we call it here.
	// 
	// Possible work-arounds:
	//		1) Load a Level manually via Client Travel / Server Travel.
	//		2) Override UEngine::TickWorldTravel() and call StopRecordingReplay() in there.
	//			- This is the correct place to use the Browse() function.
	//		3) Bind to the FCoreDelegates::OnBeginFrame delegate and call StopRecordingReplay() there.
	//			- But be sure to construct an FScopedConditionalWorldSwitcher so that the Editor Engine doesn't break.
	//			- This feels very hacky of course but it is an option if you are avoiding making custom UEngine classes.
	// 
	// Chosen work-around: 1
	//		- Which we probably would've done anyways since we want more flexability rather than just
	//			loading the default map.
	// 

	
	// Stop replay playback
	{
		bool bLoadDefaultMapOnStop; // to keep track of the old value

		// Disable bLoadDefaultMapOnStop
		UReplaySubsystem* ReplaySubsystem = GetSubsystem<UReplaySubsystem>();
		if (IsValid(ReplaySubsystem))
		{
			bLoadDefaultMapOnStop = ReplaySubsystem->bLoadDefaultMapOnStop;
			ReplaySubsystem->bLoadDefaultMapOnStop = false;
		}


		// Stop the replay playback
		StopRecordingReplay();


		// Recover bLoadDefaultMapOnStop
		if (IsValid(ReplaySubsystem))
		{
			ReplaySubsystem->bLoadDefaultMapOnStop = bLoadDefaultMapOnStop;
		}
	}


	// Travel back to our original game
	if (IsValid(GEngine))
	{
		FURL TravelURL = PreInstantReplayURL;
		TravelURL.Map = UWorld::RemovePIEPrefix(PreInstantReplayURL.Map);

		GEngine->SetClientTravel(GetWorld(), *(TravelURL.ToString()), TRAVEL_Relative);
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
				// Instant replay is playing!
				return true;
			}

		}
	}

	return false;
}
bool URDGameInstance::IsRecordingInstantReplay() const
{
	const UWorld* World = GetWorld();
	if (IsValid(World))
	{
		const UDemoNetDriver* DemoNetDriver = World->GetDemoNetDriver();
		if (IsValid(DemoNetDriver))
		{
			const FString& ActiveReplayName = DemoNetDriver->GetActiveReplayName();

			if (DemoNetDriver->IsRecording() && ActiveReplayName == InstantReplayName)
			{
				// Instant replay being recorded!
				return true;
			}

		}
	}

	return false;
}
