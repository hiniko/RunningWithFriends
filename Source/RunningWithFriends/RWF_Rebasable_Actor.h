// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RWF_Rebasable_Actor.generated.h"

UCLASS()
class RUNNINGWITHFRIENDS_API ARWF_Rebasable_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARWF_Rebasable_Actor();

	UPROPERTY()
	bool bApplyPositionOffset = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	FVector LocationOffset = FVector();

	virtual void PostNetReceiveLocationAndRotation() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
