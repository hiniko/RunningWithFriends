// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseRunner.generated.h"

UCLASS()
class RUNNINGWITHFRIENDS_API ABaseRunner : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseRunner();
	
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* SideViewCam;
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Runner Settings")
	FVector CameraOffsets = FVector(-850.0f, 0, 300);

	UPROPERTY()
	bool bShouldOffsetLocation = true;
	
	UPROPERTY()
	FVector LocationOffset = FVector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveRight(float Value);

	virtual void PostNetReceiveLocationAndRotation() override;
public:	

	UCameraComponent* GetSideViewCam() const;
	
private:
	bool bCanMove;
	float zPos;
	FVector tempPos = FVector();

};
