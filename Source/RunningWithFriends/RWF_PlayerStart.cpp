// Fill out your copyright notice in the Description page of Project Settings.


#include "RWF_Helpers.h"
#include "RWF_PlayerStart.h"

bool ARWF_PlayerStart::ClaimStartPoint(int32 ServerIndex, AController* Player)
{
	if(StartPointOwner.Get() != nullptr)
	{
		UE_LOG(LogRWF, Display, TEXT("Start Point already has owner details!"))
		return false;
	}

	StartPointOwner = Player;
	ServerSpawnIndex = ServerIndex;

	return true;
}

void ARWF_PlayerStart::ReleaseStartPoint()
{
	StartPointOwner.Reset();
	ServerSpawnIndex = 0;
}
