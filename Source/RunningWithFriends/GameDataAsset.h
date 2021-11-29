// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSectionsDataTable.h"
#include "Engine/DataAsset.h"
#include "GameDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class RUNNINGWITHFRIENDS_API UGameDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level Configuration")
	UDataTable* LevelSections;
	
};