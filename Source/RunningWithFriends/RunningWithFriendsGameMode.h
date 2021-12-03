// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LevelBuilderSubSystem.h"
#include "RWF_PlayerStart.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "RunningWithFriendsGameMode.generated.h"


UENUM()
enum class ERWF_GamePhase
{
	PreGamePhase,
	GamePhase,
	PostGamePhase,
};

UCLASS(minimalapi)
class ARunningWithFriendsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ARunningWithFriendsGameMode();
	virtual void InitGameState() override;
	
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	ERWF_GamePhase GetGamePhase() const { return CurrentPhase; }

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY()
	TArray<ARWF_PlayerStart*> PlayerStarts;

	UPROPERTY()
	TSubclassOf<ALevelSection> FirstSectionClass;

private:
	ERWF_GamePhase CurrentPhase = ERWF_GamePhase::PreGamePhase;
};