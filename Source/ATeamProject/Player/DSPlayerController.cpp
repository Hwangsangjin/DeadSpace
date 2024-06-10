// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DSPlayerController.h"

void ADSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
}
