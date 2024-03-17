// Fill out your copyright notice in the Description page of Project Settings.


#include "GetCurrentWeatherCondition.h"

AGetCurrentWeatherCondition::AGetCurrentWeatherCondition()
{
}

AGetCurrentWeatherCondition::~AGetCurrentWeatherCondition()
{
}

void AGetCurrentWeatherCondition::ProcessGetRequest(const FString& CityCodeKey)
{
	FString RequestString = "http://dataservice.accuweather.com/currentconditions/v1/" + CityCodeKey + "?apikey=JO7zMAvvprSOda7Gid91OGOhSNtOko3S";
	Super::ProcessGetRequest(RequestString);
}
