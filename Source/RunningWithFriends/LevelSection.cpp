// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSection.h"

#include "BaseRunner.h"
#include "LevelBuilderSubSystem.h"
#include "GameFramework/PlayerState.h"

// Sets default values
ALevelSection::ALevelSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LevelRoot = CreateDefaultSubobject<USceneComponent>(TEXT("LevelRoot"));
	
	SetRootComponent(LevelRoot);

	NextSectionTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("NextSectionTrigger"));
	NextSectionTrigger->AttachToComponent(LevelRoot, FAttachmentTransformRules::KeepRelativeTransform);
	NextSectionLocation = CreateDefaultSubobject<UBoxComponent>(TEXT("NextSectionLocation"));
	NextSectionLocation->AttachToComponent(LevelRoot, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ALevelSection::BeginPlay()
{
	Super::BeginPlay();

	NextSectionTrigger->bHiddenInGame = bShowTriggers;
	NextSectionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALevelSection::OnTriggerOverlap);
	
	NextSectionLocation->bHiddenInGame = bShowTriggers;

	
}

void ALevelSection::OnTriggerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(!bHasTriggeredNextSection)
	{
		if(const ABaseRunner* Runner = Cast<ABaseRunner>(OtherActor))
		{
			if(ULevelBuilderSubsystem* LevelBuilder = GetGameInstance()->GetSubsystem<ULevelBuilderSubsystem>())
			{
				LevelBuilder->SpawnNextLevelSection(Runner->GetController(), NextSectionLocation->GetComponentLocation());
				bHasTriggeredNextSection = true;
			}
		}
	}
}

void ALevelSection::PostNetReceiveLocationAndRotation()
{
	const FRepMovement& LocalRepMovement = GetReplicatedMovement();

	FIntVector RebaseVector;
	if(CurrentTrackOwner->bIsLocalPlayer)
	{
		RebaseVector.X = 150;
		RebaseVector.Y = 0;
		RebaseVector.Z = 50;
	}else
	{
		RebaseVector.X = 0;
		RebaseVector.Y = 0;
		RebaseVector.Z = 0;
	}
	
	FVector NewLocation = FRepMovement::RebaseOntoLocalOrigin(LocalRepMovement.Location, RebaseVector);
	if( RootComponent && RootComponent->IsRegistered() && (NewLocation != GetActorLocation() || LocalRepMovement.Rotation != GetActorRotation()) )
	{
		SetActorLocationAndRotation(NewLocation, LocalRepMovement.Rotation, /*bSweep=*/ false);
	}
}


// Called every frame
void ALevelSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

