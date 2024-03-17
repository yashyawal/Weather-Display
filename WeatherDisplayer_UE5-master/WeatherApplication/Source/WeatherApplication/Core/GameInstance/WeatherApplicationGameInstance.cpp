// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherApplicationGameInstance.h"
#include <WeatherApplication/Environment/WeatherManager.h>
#include <WeatherApplication/Network/NetworkManager/NetworkManager.h>

AWeatherManager* UWeatherApplicationGameInstance::GetWeatherManager() const
{
	return WeatherManager;
}
ANetworkManager* UWeatherApplicationGameInstance::GetNetworkManager() const
{
	return NetworkManager;
}
UDataTable* UWeatherApplicationGameInstance::GetWeatherDataTable() const
{
	return WeatherDataTableAsset;
}
void UWeatherApplicationGameInstance::Init()
{
	if (UWorld* World  = GetWorld())
	{ 
		WeatherManager = World->SpawnActor<AWeatherManager>(WeatherManagerAsset);
		NetworkManager = World->SpawnActor<ANetworkManager>(NetworkManagerAsset);

	}
}
