// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WeatherDisplayController.generated.h"

/**
 * Controller to add input to  Spectator
 */
UCLASS()
class WEATHERAPPLICATION_API AWeatherDisplayController : public APlayerController
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditDefaultsOnly , transient)
	float MOUSEX_SENSITYVITY = 5.0f;

private:
	UFUNCTION()
	void RotateSpectator(float Value);

	UFUNCTION()
	void Zoom(float Value);
};
