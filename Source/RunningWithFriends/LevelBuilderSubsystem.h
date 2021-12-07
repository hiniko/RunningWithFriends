﻿#pragma once
#include "LevelSection.h"
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

	UPROPERTY()
	TArray<FLevelSectionData> LevelSections;
	
	UPROPERTY()
	TMap<APlayerController*, FPlayerTrack> PlayerTracks;
	
};
