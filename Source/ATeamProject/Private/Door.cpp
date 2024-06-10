// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	IsHopeToOpen = IsOpenedCurrently;
	if (IsOpenedCurrently)
	{
		for (auto Door : DoorDataList)
		{
			FHitResult Result;
			Door.Door->K2_SetRelativeLocation(Door.OpenedPivot.GetLocation(), false, Result, false);
			Door.Door->K2_SetRelativeRotation(Door.OpenedPivot.Rotator(), false, Result, false);
		}
	}
	else
	{
		for (auto Door : DoorDataList)
		{
			FHitResult Result;
			Door.Door->K2_SetRelativeLocation(Door.ClosedPivot.GetLocation(), false, Result, false);
			Door.Door->K2_SetRelativeRotation(Door.ClosedPivot.Rotator(), false, Result, false);
		}
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsHopeToOpen != IsOpenedCurrently)
	{
		for (auto& Door : DoorDataList)
		{
			float CurrentTime = GetWorld()->GetTimeSeconds();
			FTransform ToPivot;

			if (IsHopeToOpen)
			{
				ToPivot = Door.OpenedPivot;
			}
			else
			{
				ToPivot = Door.ClosedPivot;
			}

			Process += DeltaTime / TransitionTime;
			if(1 < Process)
			{
				Process = 1.0f;
				IsProcessPassed = true;
				IsOpenedCurrently = IsHopeToOpen;
			}
			FVector3d NewTransformLocation = FMath::Lerp(Door.FromPivot.GetLocation(), ToPivot.GetLocation(), Process);
			FRotator NewTransformRotator = FMath::Lerp(Door.FromPivot.Rotator(), ToPivot.Rotator(), Process);


			FHitResult Result;
			Door.Door->K2_SetRelativeLocation(NewTransformLocation, false, Result, false);
			Door.Door->K2_SetRelativeRotation(NewTransformRotator, false, Result, false);
		}
	}
}

void ADoor::Open()
{
	if(IsProcessPassed)
	{
		PivotTime = GetWorld()->GetTimeSeconds();
		for (auto& Door : DoorDataList)
		{
			Door.FromPivot = Door.ClosedPivot;
		}
		IsHopeToOpen = true;
		Process = 0.0f;
		IsProcessPassed = false;
	}
}

void ADoor::Close()
{
	if(IsProcessPassed)
	{
		PivotTime = GetWorld()->GetTimeSeconds();
		for (auto& Door : DoorDataList)
		{
			Door.FromPivot = Door.OpenedPivot;
		}
		IsHopeToOpen = false;
		Process = 0.0f;
		IsProcessPassed = false;
	}
}

