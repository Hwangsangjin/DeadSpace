// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/DSItemData.h"
#include "DSItemWeaponData.generated.h"

/**
 * 
 */
UCLASS()
class ATEAMPROJECT_API UDSItemWeaponData : public UDSItemData
{
	GENERATED_BODY()
	
public:
	FPrimaryAssetId GetPrimaryAssetId() const override;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;
};
