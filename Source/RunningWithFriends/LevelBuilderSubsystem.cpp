#include "LevelBuilderSubSystem.h"
#include "RWF_Helpers.h"
#include "LevelSectionsDataTable.h"
#include "RWF_GameInstance.h"
#include "RWF_GameState.h"
#include "GameFramework/PlayerState.h"

DEFINE_LOG_CATEGORY(LogLevelBuilder)

static FString GLEVEL_SECTION_DATA_LOOKUP = "LevelSectionDataLookup";

void ULevelBuilderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UGameInstanceSubsystem::Initialize(Collection);

	// Load Up Level Section Data from the game mode
	if (RWF_GET_GAME_INSTANCE)
	{
		if (GameInst->LevelSectionsData)
		{
			TArray<FLevelSectionsDataTableRow*> LevelSectionsData;
			GameInst->LevelSectionsData->GetAllRows<FLevelSectionsDataTableRow>(
				GLEVEL_SECTION_DATA_LOOKUP, LevelSectionsData);
			
			for (auto* Row : LevelSectionsData)
			{
				LevelSections.Add(Row->LevelData);
			}
		}
		else
		{
			UE_LOG(LogLevelBuilder, Error, TEXT("Failed to find Level Sections data table"))
		}
	}
	
	if (LevelSections.Num() == 0)
	{
		 UE_LOG(LogLevelBuilder, Error, TEXT("Loaded 0 Level Sections"));
	}
		
}

void ULevelBuilderSubsystem::Deinitialize()
{
	UGameInstanceSubsystem::Deinitialize();
}

TSubclassOf<ALevelSection> ULevelBuilderSubsystem::GetSectionAtIndex(int32 idx) const
{
	if(idx < LevelSections.Num()) {
		return LevelSections[idx].SectionClass;
	}else
	{
		return nullptr;
	}
}

void ULevelBuilderSubsystem::UpdateLevel(const TArray<FPlayerTrack>* InPlayerTracks)
{
	UE_LOG(LogLevelBuilder, Verbose, L"Updating PlayerTracks info");

	for(const FPlayerTrack InTrack : InPlayerTracks)
	{
		if(PlayerTracks.Contains(InTrack.OwningPlayerId))
		{
			PlayerTracks[InTrack.OwningPlayerId].CurrentSections = InTrack.CurrentSections;
		}else
		{
			UE_LOG(LogLevelBuilder, Display, L"Adding new player Data for id %d", InTrack.OwningPlayerId);
			PlayerTracks.Add(InTrack.OwningPlayerId, InTrack);
		}

		// Check against what we have spawned 	
	}
	
}

TSubclassOf<ALevelSection> ULevelBuilderSubsystem::GetRandomSectionClass() const
{
	const uint32 idx = FMath::RandRange(0, LevelSections.Num()-1);
	return LevelSections[idx].SectionClass;
}

void ULevelBuilderSubsystem::SpawnNextLevelSection(AController* Player, FVector Position)
{
	if(Player == nullptr) return;
	
	if (LevelSections.Num() == 0)
	{
		UE_LOG(LogLevelBuilder, Error, TEXT("No Level Sections available"))
		return;
	}

	ARWF_GameState* GameState = Cast<ARWF_GameState>(GetWorld()->GetGameState());
	if(GameState)
	{
		GameState->AddSectionForPlayer(Player->PlayerState->GetPlayerId(),Position, GetRandomSectionClass());
	}
}
