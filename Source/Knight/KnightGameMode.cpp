// Copyright Epic Games, Inc. All Rights Reserved.

#include "KnightGameMode.h"
#include "KnightCharacter.h"

AKnightGameMode::AKnightGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AKnightCharacter::StaticClass();	
}
