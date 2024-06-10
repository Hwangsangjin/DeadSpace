// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DSItemData.h"

FPrimaryAssetId UDSItemData::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("DSItemData", GetFName());
}
