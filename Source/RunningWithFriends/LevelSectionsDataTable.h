// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LevelBuilderSubsystem.h"
#include "LevelSectionsDataTable.generated.h"


USTRUCT(BlueprintType)
struct FLevelSectionsDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLevelSectionData LevelData;
};
