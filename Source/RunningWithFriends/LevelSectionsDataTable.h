// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSection.h"
#include "Engine/DataTable.h"
#include "LevelSectionsDataTable.generated.h"

USTRUCT(BlueprintType)
struct FLevelSectionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ALevelSection> SectionClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Difficulty = 1;
};

USTRUCT(BlueprintType)
struct FLevelSectionsDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLevelSectionData LevelData;
	
};
