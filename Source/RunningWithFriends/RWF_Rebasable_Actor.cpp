// Fill out your copyright notice in the Description page of Project Settings.


#include "RWF_Rebasable_Actor.h"

// Sets default values
ARWF_Rebasable_Actor::ARWF_Rebasable_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARWF_Rebasable_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARWF_Rebasable_Actor::PostNetReceiveLocationAndRotation()
{
	const FRepMovement& LocalRepMovement = GetReplicatedMovement();
	FVector NewLocation = GetActorLocation() - LocationOffset;

	if( RootComponent && RootComponent->IsRegistered() && (NewLocation != GetActorLocation() || LocalRepMovement.Rotation != GetActorRotation()) )
	{
		SetActorLocationAndRotation(NewLocation, LocalRepMovement.Rotation, /*bSweep=*/ false);
	}
}

// Called every frame
void ARWF_Rebasable_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

