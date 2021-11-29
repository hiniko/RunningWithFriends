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
	FVector TrackPosition;

	UPROPERTY()
	TWeakObjectPtr<APlayerState> OwningPlayer;

	UPROPERTY()
	TArray<ALevelSection*> CurrentSections;

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

	void AddPlayerTrack(APlayerState* PlayerState);

	void SpawnNextLevelSection(AController* Player, const FVector Position);

private:
	UPROPERTY()
	TArray<FLevelSectionData> LevelSections;

	UPROPERTY()
	TMap<APlayerState*, FPlayerTrack> PlayerTracks;
};
