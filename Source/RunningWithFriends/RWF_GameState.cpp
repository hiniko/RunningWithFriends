// Fill out your copyright notice in the Description page of Project Settings.


#include "RWF_GameState.h"
#include "RWF_Helpers.h"
#include "RWF_PlayerState.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void ARWF_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ARWF_GameState, PlayerTracks);
}

void ARWF_GameState::OnRep_PlayerTracks_Implementation()
{
	UE_LOG(LogRWF, Display, TEXT("Replicated PlayerTracks! %s, %s"), LOCAL_ROLE_STR, REMOTE_ROLE_STR);
	if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if(ARWF_PlayerState* PlayerState = PlayerController->GetPlayerState<ARWF_PlayerState>())
		{
			for(FPlayerTrack Track: PlayerTracks)
			{
				if(Track.OwningPlayerId == PlayerState->GetPlayerId())
				{
					Track.bIsLocalPlayer = true;
					UE_LOG(LogRWF, Display, TEXT("Updating Track's local player flag for %d"), PlayerState->GetPlayerId());
					break;
				}
			}
		}
	}
}

// void ARWF_GameState::OnRep_PlayerTracks()
// {
//
// }

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
	GetWorld()->SpawnActor(SectionClass, &Position);
}