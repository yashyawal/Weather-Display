// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkRequestBase.h"
#include "GetCurrentWeatherCondition.generated.h"

/**
 * Creates and process request for getting Current weather condition and broadcasts the object to whomever it may concern 
 */
UCLASS()
class WEATHERAPPLICATION_API AGetCurrentWeatherCondition:public ANetworkRequestBase
{
	GENERATED_BODY()
public:

	AGetCurrentWeatherCondition();
	~AGetCurrentWeatherCondition();
	void ProcessGetRequest(const FString& CityCodeKey) override;
};
