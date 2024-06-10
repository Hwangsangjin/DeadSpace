// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_Shot.h"
#include "Interface/DSAnimationShotInterface.h"

void UAnimNotify_Shot::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IDSAnimationShotInterface* ShotPawn = Cast<IDSAnimationShotInterface>(MeshComp->GetOwner());
		if (ShotPawn)
		{
			ShotPawn->Shot();
		}
	}
}
