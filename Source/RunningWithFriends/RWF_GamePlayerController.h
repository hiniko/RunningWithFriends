// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RWF_GamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RUNNINGWITHFRIENDS_API ARWF_GamePlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	
};
