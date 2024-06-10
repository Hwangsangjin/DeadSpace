// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ATeamProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ATEAMPROJECT_API AATeamProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	void BeginPlay() override;
};
