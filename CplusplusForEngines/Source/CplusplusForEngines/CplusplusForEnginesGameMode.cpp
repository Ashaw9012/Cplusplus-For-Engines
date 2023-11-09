// Copyright Epic Games, Inc. All Rights Reserved.

#include "CplusplusForEnginesGameMode.h"
#include "CplusplusForEnginesCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACplusplusForEnginesGameMode::ACplusplusForEnginesGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
