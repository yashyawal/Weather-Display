// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherDisplayController.h"
#include "WeatherApplication/Player/Spectator.h"

void AWeatherDisplayController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameAndUI GameAndUIInputMode;
	SetInputMode(GameAndUIInputMode);
	bShowMouseCursor = true;
}

void AWeatherDisplayController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MouseX", this, &AWeatherDisplayController::RotateSpectator);
	InputComponent->BindAxis("Zoom", this, &AWeatherDisplayController::Zoom);
}

void AWeatherDisplayController::RotateSpectator(float Value)
{
	GetPawn()->AddControllerYawInput(Value * GetWorld()->DeltaTimeSeconds * MOUSEX_SENSITYVITY);
}

void AWeatherDisplayController::Zoom(float Value)
{
	if (Value == 0)
	{
		return;
	}

	ASpectator* Spectator = Cast<ASpectator>(GetPawn());
	if (!Spectator)
	{
		return;
	}

	if (Value > 0)
	{
		Spectator->SetZoomState(true);
	}
	else
	{
		Spectator->SetZoomState(false);
	}
}
