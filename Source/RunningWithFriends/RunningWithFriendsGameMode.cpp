// Copyright Epic Games, Inc. All Rights Reserved.

#include "RunningWithFriendsGameMode.h"

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
			if(Start->IsOccupied())
				continue;

			if(Start->ClaimStartPoint(GetNumPlayers(), Player))
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
