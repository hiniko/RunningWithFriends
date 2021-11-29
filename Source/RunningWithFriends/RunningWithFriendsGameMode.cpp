// Copyright Epic Games, Inc. All Rights Reserved.

#include "RunningWithFriendsGameMode.h"

#include "RunningWithFriends.h"
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
}

AActor* ARunningWithFriendsGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

	// Find the local position 
	for(AActor* actor: PlayerStarts)
	{
		if(APlayerStart* Start = Cast<APlayerStart>(actor))
		{
			 if(Player->IsLocalController() && Start->GetName().Contains("Local"))
			 {
			 	UE_LOG(LogRWF, Display, TEXT("Local Player is %s"), *Player->GetName())
				  return Start;
			 }

			return Start;
		}
	}
	return nullptr;
}

void ARunningWithFriendsGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
