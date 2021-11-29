// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "RWF_GameState.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerStateAdded, APlayerState*)

/**
 * 
 */
UCLASS()
class RUNNINGWITHFRIENDS_API ARWF_GameState : public AGameStateBase
{
	GENERATED_BODY()

public:


};
