#pragma once
#include "LevelSectionsDataTable.h"
#include "LevelBuilderSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogLevelBuilder, Display, All)

USTRUCT()
struct FPlayerTrack
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	FVector TrackPosition = FVector::ZeroVector;

	UPROPERTY()
	uint32 OwningPlayerID = 0;

	UPROPERTY()
	TArray<TSubclassOf<ALevelSection>> CurrentSections;

	UPROPERTY()
	bool bIsLocalPlayer = false;
};

UCLASS()
class RUNNINGWITHFRIENDS_API ULevelBuilderSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void AddPlayer(APlayerController* NewPlayer);


	void SpawnNextLevelSection(AController* Player, const FVector Position);
	TSubclassOf<ALevelSection> GetRandomSectionClass() const;
	TSubclassOf<ALevelSection> GetSectionAtIndex(int32 idx) const;
	

protected:

	UPROPERTY()
	TArray<FLevelSectionData> LevelSections;

	UPROPERTY()
	TMap<APlayerController*, FPlayerTrack> PlayerTracks;
	
};
