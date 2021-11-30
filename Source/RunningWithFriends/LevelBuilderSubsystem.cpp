#include "LevelBuilderSubSystem.h"
#include "LevelSectionsDataTable.h"
#include "RWF_GameInstance.h"
#include "RWF_Helpers.h"
#include "Engine/AssetManager.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogLevelBuilder)

static FString GLEVEL_SECTION_DATA_LOOKUP = "LevelSectionDataLookup";

ALevelBuilderReplication::ALevelBuilderReplication()
{
	bReplicates = true;
	bAlwaysRelevant = true;
}

void ALevelBuilderReplication::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALevelBuilderReplication, PlayerTracks);
}

void ALevelBuilderReplication::AddTrackInfo(FPlayerTrack& InTrack)
{
#if WITH_SERVER_CODE
	const TArray<FPlayerTrack> Tracks = PlayerTracks.FilterByPredicate([InTrack](const FPlayerTrack Track) { return Track.OwningPlayerID == InTrack.OwningPlayerID; });
	if(Tracks.Num() != 0)
	{
		UE_LOG(LogLevelBuilder, Error, TEXT("Already have a player track for ID %d, Not adding another"), InTrack.OwningPlayerID);
		return;
	}
	PlayerTracks.Add(InTrack);
#endif
}

void ALevelBuilderReplication::OnRep_PlayerTracks()
{
	// We got new track data in, do something with it
}

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

#if WITH_SERVER_CODE
	RepActor = GetWorld()->SpawnActor<ALevelBuilderReplication>();
	UE_LOG(LogLevelBuilder, Display, TEXT("Tried to create LevelBuilderRepActor got %d"), RepActor);
#endif
}

void ULevelBuilderSubsystem::Deinitialize()
{
	UGameInstanceSubsystem::Deinitialize();
}

void ULevelBuilderSubsystem::AddPlayer(APlayerController* NewPlayer)
{
#if WITH_SERVER_CODE
	if(RepActor != nullptr)
	{
		UE_LOG(LogLevelBuilder, Error, TEXT("RepActor was not valid! Bailing..."))
		return;
	}
	
	UE_LOG(LogLevelBuilder, Display, TEXT("Adding Player for controller %d"), NewPlayer->GetUniqueID());
	FPlayerTrack Track;
	Track.OwningPlayerID = NewPlayer->GetUniqueID();
	Track.TrackPosition = FVector();
	RepActor->AddTrackInfo(Track);
#endif
}

void ULevelBuilderSubsystem::SpawnNextLevelSection(AController* Player, FVector Position)
{
#if WITH_SERVER_CODE
	if (LevelSections.Num() == 0)
	{
		UE_LOG(LogLevelBuilder, Error, TEXT("No Level Sections available"))
		return;
	}

	const int32 idx = FMath::RandRange(0, LevelSections.Num()-1);
	GetWorld()->SpawnActor(LevelSections[idx].SectionClass, &Position);
	UE_LOG(LogLevelBuilder, Verbose, TEXT("Spawning in new level at %f, %f, %f"), Position.X, Position.Y, Position.Z);
#endif 
}
