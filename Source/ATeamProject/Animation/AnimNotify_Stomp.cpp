// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Stomp.h"
#include "Interface/DSAnimationStompInterface.h"

void UAnimNotify_Stomp::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IDSAnimationStompInterface* StompPawn = Cast<IDSAnimationStompInterface>(MeshComp->GetOwner());
		if (StompPawn)
		{
			StompPawn->Stomp();
		}
	}
}
