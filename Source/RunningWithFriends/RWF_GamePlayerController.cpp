// Fill out your copyright notice in the Description page of Project Settings.


#include "RWF_GamePlayerController.h"
#include "GameFramework/PlayerState.h"
#include "RWF_Helpers.h"

void ARWF_GamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(GetNetMode() < NM_Client && GetRemoteRole() == ROLE_None)
	{
		UE_LOG(LogRWF, Display, L"PC: SERVER  %s with %s", LOCAL_ROLE_STR, REMOTE_ROLE_STR);
	}else
	{
		UE_LOG(LogRWF, Display, L"PC: CLIENT %s with %s", LOCAL_ROLE_STR, REMOTE_ROLE_STR);
	}
}

void ARWF_GamePlayerController::TickActor(float DeltaTime, ELevelTick Tick, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, Tick, ThisTickFunction);
	
	if(GEngine)
	{
		const int32 PlayerId = (PlayerState) ? PlayerState->GetPlayerId() :  -1;
		GEngine->AddOnScreenDebugMessage(10000 + PlayerId, 1, FColor::Yellow, FString::Printf(L"This PlayerID: %d ", PlayerId));
	}
}
