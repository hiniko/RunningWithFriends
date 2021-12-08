// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelBuilderSubsystem.h"
#include "GameFramework/GameState.h"
#include "RWF_GameState.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerStateAdded, APlayerState*)

/**
 * 
 */
UCLASS()
class RUNNINGWITHFRIENDS_API ARWF_GameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Client, Reliable)
	virtual void OnRep_PlayerTracks();
	
	UPROPERTY(ReplicatedUsing=OnRep_PlayerTracks)
	TArray<FPlayerTrack> PlayerTracks;
	
	void AddTrackInfo(AController* NewPlayer);

	UFUNCTION(Server, Reliable)
	void AddSectionForPlayer(int32 PlayerID, FVector Position, TSubclassOf<ALevelSection> SectionClass);


private:
	uint32 LastTrackUpdate = 0;
	uint32 CurrentTrackUpdate = 0;

};