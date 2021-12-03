#include "LevelBuilderSubSystem.h"
#include "LevelSectionsDataTable.h"
#include "RWF_GameInstance.h"
#include "RWF_GameState.h"
#include "RWF_Helpers.h"
#include "Engine/AssetManager.h"

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
		GameState->AddSectionForPlayer(Player->GetUniqueID(), Position, GetRandomSectionClass());
	}
}
