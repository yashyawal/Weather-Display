// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include <GameFrameWork/Actor.h>
#include "CurrentWeatherConditionResponse.generated.h"
/**
 * Response object to store response from current weather condition API 
 */
UCLASS()
class WEATHERAPPLICATION_API ACurrentWeatherConditionResponse:public AActor
{
	GENERATED_BODY()
public:
	ACurrentWeatherConditionResponse();
	~ACurrentWeatherConditionResponse();

	void SetValues(FString InWeatherText , int16 WeatherIcon , bool IsDayTime , float Temperature , FString InClockTime );
	const FString& GetWeatherText() const;
	int16 GetWeatherIcon() const;
	bool GetIsDayTime() const;
	float GetTemperature() const;
	const FString& GetCurrentTime() const;
private:
	UPROPERTY()
	FString WeatherText;
	UPROPERTY()
	int16 WeatherIcon;
	UPROPERTY()
	bool bIsDayTime;
	UPROPERTY()
	float Temperature;
	UPROPERTY()
    FString CurrentTime;
};
