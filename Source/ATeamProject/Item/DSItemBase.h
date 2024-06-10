// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSItemBase.generated.h"

UCLASS()
class ATEAMPROJECT_API ADSItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADSItemBase();

	FORCEINLINE class UBoxComponent* GetTrigger() { return Trigger; }

protected:
	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TObjectPtr<class UBoxComponent> Trigger;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Weapon)
	TObjectPtr<class USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Item)
	TObjectPtr<class UDSItemData> Item;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);
};
