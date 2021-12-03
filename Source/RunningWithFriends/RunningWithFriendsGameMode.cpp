// Copyright Epic Games, Inc. All Rights Reserved.

#include "RunningWithFriendsGameMode.h"

#include "LevelBuilderSubSystem.h"
#include "RWF_GameState.h"
#include "RWF_Helpers.h"
#include "RWF_PlayerStart.h"
#include "ToolBuilderUtil.h"
#include "Kismet/GameplayStatics.h"


ARunningWithFriendsGameMode::ARunningWithFriendsGameMode()
{
	// // set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	// if (PlayerPawnBPClass.Class != NULL)
	// {
	// 	DefaultPawnClass = PlayerPawnBPClass.Class;
	// }
}

void ARunningWithFriendsGameMode::InitGameState()
{
	Super::InitGameState();
	

	// Find player starts and spawn in new Sections below them
	TArray<AActor*> Starts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARWF_PlayerStart::StaticClass(), Starts);
	for(auto Actor : Starts)
	{
		if(ARWF_PlayerStart* Start = Cast<ARWF_PlayerStart>(Actor))
		{
			PlayerStarts.Add(Start);
		}
	}
	UE_LOG(LogRWF, Display, TEXT("Found %d Player Starts"), PlayerStarts.Num());

	ULevelBuilderSubsystem* LevelBuilder = GetGameInstance()->GetSubsystem<ULevelBuilderSubsystem>();
	if(LevelBuilder == nullptr)
	{
		UE_LOG(LogRWF, Error, L"Failed to find LevelBuilder Subsystem!")
		return;
	}
	
	FirstSectionClass = LevelBuilder->GetSectionAtIndex(3);
}

AActor* ARunningWithFriendsGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if(PlayerStarts.Num() == 0)
	{
		UE_LOG(LogRWF, Display, TEXT("GameMode: Failed to find any APlayerStarts in Map!"))
		return nullptr;
	}
	
	ULevelBuilderSubsystem* LevelBuilder = GetGameInstance()->GetSubsystem<ULevelBuilderSubsystem>();
	if(LevelBuilder == nullptr)
	{
		UE_LOG(LogRWF, Error, L"Failed to find LevelBuilder Subsystem!")
		return nullptr;
	}

	for(ARWF_PlayerStart* Start: PlayerStarts)
	{
		if(Start->IsOccupied())
			 continue;

		if(Start->ClaimStartPoint(GetNumPlayers(), Player))
		{
			ARWF_GameState* State = GetGameState<ARWF_GameState>();
			const FVector SectionPos = Start->GetActorLocation() - FVector(0,-250,100);
			// Add player ot the track lists	
			State->AddTrackInfo(Player);
			State->AddSectionForPlayer(Player->GetUniqueID(), SectionPos, FirstSectionClass);
			return Start;
		}
	}

	UE_LOG(LogRWF, Display, TEXT("GameMode: Failed to find an unoccupied server start for %s"), Player->GetUniqueID());
	return nullptr;
}

void ARunningWithFriendsGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	UE_LOG(LogRWF, Display, TEXT("Handling Starting New Player: %s"), *NewPlayer->GetName())
	
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	
// 	if(RWF_GET_GAME_INSTANCE)
// 	{
// 		ULevelBuilderSubsystem* LevelBuilderSubsystem = GameInst->GetSubsystem<ULevelBuilderSubsystem>();
// 		if(LevelBuilderSubsystem)
// 		{
// 			LevelBuilderSubsystem->AddPlayer(NewPlayer);
// 			const ARWF_PlayerState* PlayerState = NewPlayer->GetPlayerState<ARWF_PlayerState>();
// 			UE_LOG(LogRWF, Display, TEXT("Got PlayerState with PlayerID %d"), PlayerState->GetPlayerId());
// 		}
// 	}
	
}

void ARunningWithFriendsGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
