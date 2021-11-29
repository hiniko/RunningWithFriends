// Fill out your copyright notice in the Description page of Project Settings.


#include "RWF_PlayerStart.h"
#include "RunningWithFriends.h"

bool ARWF_PlayerStart::ClaimStartPoint(int32 ServerIndex, AController* Player)
{
	if(bOccupiedByPlayer && StartPointOwner.Get() != nullptr)
	{
		UE_LOG(LogRWF, Display, TEXT("Start Point already has owner details!"))
		return false;
	}

	bOccupiedByPlayer = true;
	StartPointOwner = Player;
	ServerSpawnIndex = ServerIndex;

	return true;
}
