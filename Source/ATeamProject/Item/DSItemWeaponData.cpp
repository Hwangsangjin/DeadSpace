// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DSItemWeaponData.h"

FPrimaryAssetId UDSItemWeaponData::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("DSItemData", GetFName());
}
