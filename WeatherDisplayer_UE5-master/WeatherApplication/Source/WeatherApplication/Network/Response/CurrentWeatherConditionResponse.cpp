// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrentWeatherConditionResponse.h"

ACurrentWeatherConditionResponse::ACurrentWeatherConditionResponse()
{
}

ACurrentWeatherConditionResponse::~ACurrentWeatherConditionResponse()
{
}

void ACurrentWeatherConditionResponse::SetValues(FString InWeatherText, int16 InWeatherIcon, bool InIsDayTime, float InTemperature , FString InClockTime)
{
	WeatherText = InWeatherText;
	WeatherIcon = InWeatherIcon;
	bIsDayTime = InIsDayTime;
	Temperature = InTemperature;
	CurrentTime = InClockTime;
}

const FString& ACurrentWeatherConditionResponse::GetWeatherText() const
{
	return WeatherText;
}

int16 ACurrentWeatherConditionResponse::GetWeatherIcon() const
{
	return WeatherIcon;
}

bool ACurrentWeatherConditionResponse::GetIsDayTime() const
{
	return bIsDayTime;
}

float ACurrentWeatherConditionResponse::GetTemperature() const
{
	return Temperature;
}

const FString& ACurrentWeatherConditionResponse::GetCurrentTime() const
{
	return CurrentTime;
}
