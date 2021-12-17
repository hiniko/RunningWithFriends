// Fill out your copyright notice in the Description page of Project Settings.


#include "RWF_GameState.h"

#include "RWF_Helpers.h"
#include "RWF_PlayerState.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ARWF_GameState::ARWF_GameState()
{
	if(auto* LevelBuilder = GetGameInstance()->GetSubsystem<ULevelBuilderSubsystem>())
	{
		GetOnPlayerTracksUpdated().AddUObject(LevelBuilder, ULevelBuilderSubsystem::UpdateLevel);
	}
}

void ARWF_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Always notify clients of updates to the player tracks
	DOREPLIFETIME_CONDITION_NOTIFY(ARWF_GameState, PlayerTracks, COND_None, REPNOTIFY_Always);
}


void ARWF_GameState::OnRep_PlayerTracks()
{
	UE_LOG(LogRWF, Display, TEXT("Player Tracks Reped, %d"), GetUniqueID());
}

void ARWF_GameState::AddTrackInfo(AController* NewPlayer)
{
	UE_LOG(LogLevelBuilder, Display, TEXT("Adding Player track for Player Id%d"), NewPlayer->PlayerState->GetPlayerId());
	FPlayerTrack Track;
	Track.OwningPlayerId = NewPlayer->PlayerState->GetPlayerId();
	Track.TrackPosition = FVector::ZeroVector;
	PlayerTracks.Add(Track);
}

void ARWF_GameState::AddSectionForPlayer_Implementation(int32 PlayerID, FVector Position, TSubclassOf<ALevelSection> SectionClass)
{
	auto* Track = PlayerTracks.FindByPredicate([PlayerID](const FPlayerTrack T) { return T.OwningPlayerId == PlayerID; });
	if(Track == nullptr)
	{
		UE_LOG(LogRWF, Error, L"Unable to find Track info for player %d", PlayerID);
		return;
	}
	
	Track->CurrentSections.Add(SectionClass);
	//GetWorld()->SpawnActor(SectionClass, &Position);

	if(GetNetMode() == NM_ListenServer)
	{
		OnRep_PlayerTracks();
	}
}
