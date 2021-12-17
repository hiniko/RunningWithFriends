// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "LevelSection.generated.h"

UCLASS()
class RUNNINGWITHFRIENDS_API ALevelSection : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelSection();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Section | Stats")
	float Difficulty = 1.f;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UBoxComponent* GetNextSectionTrigger() const { return NextSectionTrigger; }
	UBoxComponent* GetNextSectionLocation() const { return NextSectionLocation; }

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTriggerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Section | Triggers")
	UBoxComponent* NextSectionTrigger;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Section | Triggers")
	UBoxComponent* NextSectionLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Section | Debug")
	bool bShowTriggers = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* LevelRoot;
	
	bool bHasTriggeredNextSection = false;
};
