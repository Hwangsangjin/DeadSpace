// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DSGameMode.h"

ADSGameMode::ADSGameMode()
{
	// �⺻ �� Ŭ����
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/Blueprints/BP_IsaacClarke.BP_IsaacClarke_C"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}
	
	// �÷��̾� ��Ʈ�ѷ�
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ATeamProject.DSPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
