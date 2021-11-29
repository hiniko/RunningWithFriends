// Fill out your copyright notice in the Description page of Project Settings.


#include "RWF_PlayerState.h"
#include "RWF_GameInstance.h"
#include "RunningWithFriends.h"

void ARWF_PlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	// if(HasAuthority())
	// {
	// 	if(const URWF_GameInstance* GameInst = Cast<URWF_GameInstance>(GetGameInstance()))
	// 	{
	// 		if(ULevelBuilderSubsystem* LevelBuilder = GameInst->GetSubsystem<ULevelBuilderSubsystem>())
	// 		{
	// 			LevelBuilder->AddPlayerTrack(this);
	// 			UE_LOG(LogRWF, Display, TEXT("Setup Player %d, in Level Builder"), GetUniqueID());
	// 		}
	// 	}
	// }
}
 