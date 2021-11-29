// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRunner.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseRunner::ABaseRunner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SideViewCam = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCam"));
	SideViewCam->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 1080.0f, 0.f);


	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->JumpZVelocity = 1000.0f;
    GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	tempPos = GetActorLocation();
	zPos = tempPos.Z + CameraOffsets.Z;
	
    
}

// Called when the game starts or when spawned
void ABaseRunner::BeginPlay()
{
	Super::BeginPlay();
	bCanMove = true;
}

void ABaseRunner::MoveRight(float Value) 
{
	if(bCanMove)
		AddMovementInput(FVector(0.f, 1.0f,0.f), Value);
}

void ABaseRunner::PostNetReceiveLocationAndRotation()
{
	if(bShouldOffsetLocation)
	{
		const FRepMovement& LocalRepMovement = GetReplicatedMovement();
		FVector NewLocation = GetActorLocation() - LocationOffset;

		if( RootComponent && RootComponent->IsRegistered() && (NewLocation != GetActorLocation() || LocalRepMovement.Rotation != GetActorRotation()) )
		{
			SetActorLocationAndRotation(NewLocation, LocalRepMovement.Rotation, /*bSweep=*/ false);
		}
	}
}

// Called every frame
void ABaseRunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	tempPos = GetActorLocation();
	tempPos.X -= CameraOffsets.X;
	tempPos.Z = CameraOffsets.Z;
	SideViewCam->SetWorldLocation(tempPos);

}

// Called to bind functionality to input
void ABaseRunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseRunner::MoveRight);
	

}

void ABaseRunner::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}


UCameraComponent* ABaseRunner::GetSideViewCam() const
{
	return SideViewCam;
}

