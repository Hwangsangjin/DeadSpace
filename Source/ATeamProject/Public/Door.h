// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

USTRUCT(BlueprintType)
struct FDoorData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform OpenedPivot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform ClosedPivot;

	FTransform FromPivot;
};

UCLASS()
class ATEAMPROJECT_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FDoorData> DoorDataList;

public:
	UFUNCTION(BlueprintCallable, CallInEditor)
	void Open();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Close();

public:
	UPROPERTY(BlueprintReadOnly)
	float PivotTime = 0;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float TransitionTime = 10;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	bool IsOpenedCurrently = false;

	UPROPERTY(BlueprintReadOnly)
	bool IsHopeToOpen = false;

	UPROPERTY(BlueprintReadOnly)
	bool IsProcessPassed = true;

private:
	float Process = 0.0f;
};
