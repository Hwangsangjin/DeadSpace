// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DSItemBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interface/DSCharacterItemInterface.h"
#include "Engine/AssetManager.h"
#include "DSItemData.h"

// Sets default values
ADSItemBase::ADSItemBase()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);

	Trigger->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));

	Mesh->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void ADSItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//UAssetManager& AssetManager = UAssetManager::Get();

	//TArray<FPrimaryAssetId> Assets;
	//AssetManager.GetPrimaryAssetIdList(TEXT("DSItemData"), Assets);
	//ensure(Assets.Num() > 0);

	//FSoftObjectPtr AssetPtr(AssetManager.GetPrimaryAssetPath(Assets[0]));
	//if (AssetPtr.IsPending())
	//{
		//AssetPtr.LoadSynchronous();
	//}

	//Item = Cast<UDSItemData>(AssetPtr.Get());
	//ensure(Item);

	//Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADSItemBase::OnOverlapBegin);
}

void ADSItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (!Item)
	{
		Destroy();
		return;
	}

	IDSCharacterItemInterface* OverlappingPawn = Cast<IDSCharacterItemInterface>(OtherActor);
	if (OverlappingPawn)
	{
		OverlappingPawn->TakeItem(Item);
	}

	Mesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);
}

