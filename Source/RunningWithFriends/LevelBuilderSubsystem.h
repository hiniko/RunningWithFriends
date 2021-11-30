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
	uint32 OwningPlayerID;

	UPROPERTY()
	TArray<ALevelSection*> CurrentSections;

	UPROPERTY()
	bool bIsLocalPlayer = false;
};

UCLASS()
class RUNNINGWITHFRIENDS_API ALevelBuilderReplication: public AInfo
{
	GENERATED_BODY()

friend class ULevelBuilderSubsystem;

public:
	ALevelBuilderReplication();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	virtual void OnRep_PlayerTracks();
	
	UPROPERTY(ReplicatedUsing=OnRep_PlayerTracks)
	TArray<FPlayerTrack> PlayerTracks;

private:
	void AddTrackInfo(FPlayerTrack &Track);

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

protected:
	UPROPERTY()
	ALevelBuilderReplication* RepActor;

	UPROPERTY()
	TArray<FLevelSectionData> LevelSections;

	UPROPERTY()
	TMap<APlayerController*, FPlayerTrack> PlayerTracks;
	
};
