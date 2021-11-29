// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RWF_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RUNNINGWITHFRIENDS_API ARWF_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
};
