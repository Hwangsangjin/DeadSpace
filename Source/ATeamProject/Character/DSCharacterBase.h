// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DSCharacterBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDSCharacter, Log, All)

UENUM()
enum class ECharacterControlType : uint8
{
	Default
};

UCLASS()
class ATEAMPROJECT_API ADSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADSCharacterBase();

	virtual void PostInitializeComponents() override;

protected:
	// Control Data Section
	virtual void SetCharacterControlData(const class UDSCharacterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UDSCharacterControlData*> CharacterControlManager;
};
