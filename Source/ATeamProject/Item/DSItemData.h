// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DSItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	Potion,
	Ammo
};

/**
 * 
 */
UCLASS()
class ATEAMPROJECT_API UDSItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	FPrimaryAssetId GetPrimaryAssetId() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemType)
	EItemType ItemType;
};
