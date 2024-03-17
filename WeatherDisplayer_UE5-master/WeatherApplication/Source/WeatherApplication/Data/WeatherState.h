// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include <NiagaraComponent.h>
#include <WeatherApplication/Environment/WeatherConditions.h>
#include <WeatherState.generated.h>

/**
 * Structure represents row for specific weather condition by combining different weather conditions  
 */
UENUM()
enum EWeatherComponent
{
	ECLOUD,
	ERAIN,
	ESNOW,
	ETHUNDER
};
USTRUCT()
struct WEATHERAPPLICATION_API FWeatherState:public FTableRowBase 
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* WeatherIcon; //UI 

	UPROPERTY(EditDefaultsOnly)
	uint32 WeatherID;//Uniqe identifier

	UPROPERTY(EditDefaultsOnly)
	float SunBrightness;//Environment

	UPROPERTY(EditDefaultsOnly)
	float MoonBrightness;//Environment

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EWeatherComponent>> WetherComponentList;//Environment

	UPROPERTY(EditDefaultsOnly)
	float CloudDensity;
    
	UPROPERTY(EditDefaultsOnly)
	float RainDensity;

	UPROPERTY(EditDefaultsOnly)
	float SnowDensity;

	void UpdateWeatherComponents();
};