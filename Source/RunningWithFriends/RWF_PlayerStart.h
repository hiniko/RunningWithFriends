// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "RWF_PlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class RUNNINGWITHFRIENDS_API ARWF_PlayerStart : public APlayerStart
{
	GENERATED_BODY()
	
public: 

	UPROPERTY(BlueprintReadOnly)
	bool bOccupiedByPlayer;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AController> StartPointOwner;

	UPROPERTY(BlueprintReadOnly)
	int32 ServerSpawnIndex = 0;
	
	UPROPERTY(BlueprintReadOnly)
	int32 ClientSpawnIndex = 0;
	
	bool ClaimStartPoint(int32 INT32, AController* Player);
};
