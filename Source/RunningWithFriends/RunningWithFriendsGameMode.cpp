// Copyright Epic Games, Inc. All Rights Reserved.

#include "RunningWithFriendsGameMode.h"

#include "RunningWithFriends.h"
#include "RWF_GameInstance.h"
#include "RWF_PlayerStart.h"
#include "RWF_PlayerState.h"
#include "ToolBuilderUtil.h"
#include "GameFramework/PlayerStart.h"
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

	bStartPlayersAsSpectators = 0;
}

AActor* ARunningWithFriendsGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARWF_PlayerStart::StaticClass(), PlayerStarts);

	if(PlayerStarts.Num() == 0)
	{
		UE_LOG(LogRWF, Display, TEXT("GameMode: Failed to find any APlayerStarts in Map!"))
		return nullptr;
	}

	for(AActor* Actor: PlayerStarts)
	{
		if(ARWF_PlayerStart* Start = Cast<ARWF_PlayerStart>(Actor))
		{
			if(Start->bOccupiedByPlayer)
				continue;

			bool bClaimed = Start->ClaimStartPoint(GetNumPlayers(), Player);
			
			if(bClaimed)
			{
				return Start;
			}
		}
	}

	UE_LOG(LogRWF, Display, TEXT("GameMode: Failed to find an unoccupied server start for %s"), Player->GetUniqueID());
	return nullptr;
}

void ARunningWithFriendsGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	UE_LOG(LogRWF, Display, TEXT("Handling Starting New Player: %s"), *NewPlayer->GetName()) 
	
#if WITH_SERVER_CODE
	if(URWF_GameInstance* GameInst = Cast<URWF_GameInstance>(GetGameInstance()))
	{

		ULevelBuilderSubsystem* LevelBuilderSubsystem = GameInst->GetSubsystem<ULevelBuilderSubsystem>();
		if(LevelBuilderSubsystem)
		{
			LevelBuilderSubsystem->AddPlayer(NewPlayer);
			ARWF_PlayerState* PlayerState = NewPlayer->GetPlayerState<ARWF_PlayerState>();
			UE_LOG(LogRWF, Display, TEXT("Got PlayerState with PlayerID %d"), PlayerState->GetPlayerId());
			
		}
	}
#endif
	
}

void ARunningWithFriendsGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
