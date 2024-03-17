// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkRequestBase.h"
#include "GetCityCode.generated.h"
/**
 * Class responsible for creating and processing request for getting city Code , upon completion of the request it broadcasts the CityCode 
 * to whomever it may concern .
 */

UCLASS()
class WEATHERAPPLICATION_API AGetCityCode:public ANetworkRequestBase
{
	GENERATED_BODY()
public:
	AGetCityCode();
	~AGetCityCode();
	void ProcessGetRequest(const FString& CityName) override;
};
