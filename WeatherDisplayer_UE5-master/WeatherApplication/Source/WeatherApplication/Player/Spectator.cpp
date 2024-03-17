// Fill out your copyright notice in the Description page of Project Settings.


#include "Spectator.h"
#include <GameFrameWork/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/StaticMeshComponent.h>
// Sets default values
ASpectator::ASpectator()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!LookAtComponent)
	{
		LookAtComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ViewPositionComponent"));
		
	}
	if (!SpringArmComponent)
	{
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoomComponent"));
		SpringArmComponent->SetupAttachment(LookAtComponent);
	}
	if (!CameraComponent)
	{
		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
		CameraComponent->SetupAttachment(SpringArmComponent);
	}
}

// Called when the game starts or when spawned
void ASpectator::BeginPlay()
{
	Super::BeginPlay();
	LookAtComponent->SetWorldLocation(StartingPosition);
	OriginalRelativeCameraLocation = CameraComponent->GetRelativeLocation();
	RelativeZoomedTargetLocation = (OriginalRelativeCameraLocation + CameraComponent->GetForwardVector() * 300);
}

// Called every frame
void ASpectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bShouldZoom)
	{
		FVector CurrentCameraRelativeLocation = CameraComponent->GetRelativeLocation();
		FVector InterPolatedRelativeLocation = FMath::Lerp<FVector>(CurrentCameraRelativeLocation, RelativeZoomedTargetLocation, DeltaTime);
		CameraComponent->SetRelativeLocation(InterPolatedRelativeLocation);
	}
	else
	{
		FVector CurrentCameraRelativeLocation = CameraComponent->GetRelativeLocation();
		FVector InterPolatedRelativeLocation = FMath::Lerp<FVector>(CurrentCameraRelativeLocation, OriginalRelativeCameraLocation, DeltaTime);
		CameraComponent->SetRelativeLocation(InterPolatedRelativeLocation);
	}

}

void ASpectator::SetZoomState(bool bZoomState)
{
	bShouldZoom = bZoomState;
}


