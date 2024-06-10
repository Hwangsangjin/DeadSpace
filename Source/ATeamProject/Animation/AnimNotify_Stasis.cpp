// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_Stasis.h"
#include "Interface/DSAnimationStasisInterface.h"

void UAnimNotify_Stasis::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IDSAnimationStasisInterface* StasisPawn = Cast<IDSAnimationStasisInterface>(MeshComp->GetOwner());
		if (StasisPawn)
		{
			StasisPawn->Stasis();
		}
	}
}
