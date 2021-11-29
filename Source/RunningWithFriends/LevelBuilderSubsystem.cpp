#include "LevelBuilderSubSystem.h"
#include "LevelSectionsDataTable.h"
#include "RWF_GameInstance.h"
#include "RWF_PlayerState.h"
#include "Engine/AssetManager.h"

DEFINE_LOG_CATEGORY(LogLevelBuilder)

static FString GLEVEL_SECTION_DATA_LOOKUP = "LevelSectionDataLookup";

void ULevelBuilderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UGameInstanceSubsystem::Initialize(Collection);

	const URWF_GameInstance* GameInst = Cast<URWF_GameInstance>(GetGameInstance());
	if (GameInst)
	{
		// Load Up Level Section Data from the game mode
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

void ULevelBuilderSubsystem::AddPlayerTrack(APlayerState* PlayerState)
{
	FPlayerTrack Track;
	
	Track.OwningPlayer = PlayerState;
	Track.TrackPosition = FVector();
	PlayerTracks.Add(PlayerState, Track);
	
	UE_LOG(LogLevelBuilder, Display, TEXT("Added Track for Player: %d"), PlayerState->GetUniqueID());
}

void ULevelBuilderSubsystem::SpawnNextLevelSection(AController* Player, FVector Position)
{
	if (LevelSections.Num() == 0)
	{
		UE_LOG(LogLevelBuilder, Error, TEXT("No Level Sections available"))
		return;
	}

	const int32 idx = FMath::RandRange(0, LevelSections.Num()-1);
	GetWorld()->SpawnActor(LevelSections[idx].SectionClass, &Position);
	UE_LOG(LogLevelBuilder, Verbose, TEXT("Spawning in new level at %f, %f, %f"), Position.X, Position.Y, Position.Z);
}
