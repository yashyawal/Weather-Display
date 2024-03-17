// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Spectator.generated.h"

class USceneComponent;
class UCameraComponent;
class USpringArmComponent;
/// <summary>
/// Actor Responsible for display , zoom , pan 
/// </summary>
UCLASS()
class WEATHERAPPLICATION_API ASpectator : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpectator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* LookAtComponent;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	FVector StartingPosition;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetZoomState(bool bZoomState);

private:
	bool bShouldZoom;
	FVector OriginalRelativeCameraLocation;
	FVector RelativeZoomedTargetLocation;
	FVector RelativeUnZoomedTargetLocation;
};
