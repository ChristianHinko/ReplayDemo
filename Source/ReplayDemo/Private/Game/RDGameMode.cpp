// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/RDGameMode.h"

#include "Character/RDCharacter.h"



ARDGameMode::ARDGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = ARDCharacter::StaticClass();
}
