// Fill out your copyright notice in the Description page of Project Settings.


#include "RWF_GameState.h"
#include "RWF_Helpers.h"
#include "Net/UnrealNetwork.h"

void ARWF_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ARWF_GameState, PlayerTracks);
}

void ARWF_GameState::OnRep_PlayerTracks()
{
	
}


void ARWF_GameState::AddTrackInfo(AController* NewPlayer)
{
	UE_LOG(LogLevelBuilder, Display, TEXT("Adding Player for controller %d"), NewPlayer->GetUniqueID());
	FPlayerTrack Track;
	Track.OwningPlayerID = NewPlayer->GetUniqueID();
	Track.TrackPosition = FVector::ZeroVector;
	PlayerTracks.Add(Track);
}

void ARWF_GameState::AddSectionForPlayer_Implementation(uint32 PlayerID, FVector Position, TSubclassOf<ALevelSection> SectionClass)
{
	auto* Track = PlayerTracks.FindByPredicate([PlayerID](const FPlayerTrack T) { return T.OwningPlayerID == PlayerID; });
	if(Track == nullptr)
	{
		UE_LOG(LogRWF, Error, L"Unable to find Track info for player %d", PlayerID);
		return;
	}

	Track->CurrentSections.Add(SectionClass);
	GetWorld()->SpawnActor(SectionClass, &Position);
}