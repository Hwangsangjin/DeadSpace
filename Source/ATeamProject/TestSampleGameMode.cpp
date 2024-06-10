// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestSampleGameMode.h"
#include "TestSampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestSampleGameMode::ATestSampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
