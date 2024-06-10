// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_Reload.h"
#include "Interface/DSAnimationReloadInterface.h"

void UAnimNotify_Reload::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IDSAnimationReloadInterface* ReloadPawn = Cast<IDSAnimationReloadInterface>(MeshComp->GetOwner());
		if (ReloadPawn)
		{
			ReloadPawn->Reload();
		}
	}
}
