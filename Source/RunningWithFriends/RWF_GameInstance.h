// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "RWF_GameInstance.generated.h"


UCLASS()
class RUNNINGWITHFRIENDS_API URWF_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Game Settings")
	UDataTable*  LevelSectionsData;
	
};
