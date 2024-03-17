// Fill out your copyright notice in the Description page of Project Settings.


#include "GetCityCode.h"

AGetCityCode::AGetCityCode()
{
}

AGetCityCode::~AGetCityCode()
{
}

void AGetCityCode::ProcessGetRequest(const FString& CityName)
{
	//TODO: Change the hard coded URL to it's field name 
	FString RequestString = "http://dataservice.accuweather.com/locations/v1/cities/search?apikey=JO7zMAvvprSOda7Gid91OGOhSNtOko3S&q=" + CityName;
	
	Super::ProcessGetRequest(RequestString);
}
