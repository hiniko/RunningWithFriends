// Fill out your copyright notice in the Description page of Project Settings.


#include "RWF_GameState.h"

#include "Net/UnrealNetwork.h"

void ARWF_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ARWF_GameState, PlayerTracks);
}

void ARWF_GameState::OnRep_PlayerTracks()
{
	
}

void ARWF_GameState::AddTrackInfo(APlayerController* NewPlayer)
{
	UE_LOG(LogLevelBuilder, Display, TEXT("Adding Player for controller %d"), NewPlayer->GetUniqueID());
	FPlayerTrack Track;
	Track.OwningPlayerID = NewPlayer->GetUniqueID();
	Track.TrackPosition = FVector::ZeroVector;
	PlayerTracks.Add(Track);
}
