// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DSCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DSCharacterControlData.h"

DEFINE_LOG_CATEGORY(LogDSCharacter)

// Sets default values
ADSCharacterBase::ADSCharacterBase()
{
	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	// Control Data
	static ConstructorHelpers::FObjectFinder<UDSCharacterControlData> ControlDataRef(TEXT("/Script/DeadSpace.DSCharacterControlData'/Game/Characters/DSCharacterControlData.DSCharacterControlData'"));
	if (ControlDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Default, ControlDataRef.Object);
	}
}

void ADSCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ADSCharacterBase::SetCharacterControlData(const UDSCharacterControlData* CharacterControlData)
{
	// Pawn
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

	// Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
}
