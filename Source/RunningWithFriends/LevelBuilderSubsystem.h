#pragma once
#include "LevelSection.h"
#include "RWF_GameState.h"
#include "RWF_PlayerStart.h"
#include "LevelBuilderSubsystem.generated.h" 

DECLARE_LOG_CATEGORY_EXTERN(LogLevelBuilder, Display, All)

USTRUCT(BlueprintType)
struct FLevelSectionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ALevelSection> SectionClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Difficulty = 1;
};

USTRUCT(BlueprintType)
struct FPlayerTrack
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	FVector TrackPosition = FVector::ZeroVector;

	UPROPERTY()
	int32 OwningPlayerId = 0;

	UPROPERTY()
	TArray<TSubclassOf<ALevelSection>> CurrentSections;

	UPROPERTY()
	bool bIsLocalPlayer = false;
};


USTRUCT()
struct FTrackSection
{
	GENERATED_BODY()

	UPROPERTY()
	ALevelSection* Section;

	UPROPERTY()
	TSubclassOf<ALevelSection> SectionClass;

	UPROPERTY()
	bool IsActive = false;
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

	void UpdateLevel(const TArray<FPlayerTrack>* PlayerTracks);

	void RegisterPlayerStarts(TArray<ARWF_PlayerStart> PlayerStarts);

private:
	TMap<int32, FPlayerTrack> PlayerTracks;
	TMap<int32, FTrackSection> SectionData;
	
	UPROPERTY()
	TArray<FLevelSectionData> LevelSections;
};
