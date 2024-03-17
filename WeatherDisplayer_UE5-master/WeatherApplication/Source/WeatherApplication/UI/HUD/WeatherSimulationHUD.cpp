// Fill out your copyright notice in the Description page of Project Settings.
#include "WeatherSimulationHUD.h"
#include <WeatherApplication/UI/Widgets/WeatherSimulationScreen.h>
#include <WeatherApplication/Player/WeatherDisplayController.h>
#include <Components/VerticalBox.h>
#include <WeatherApplication/UI/Widgets/CityOption.h>
#include <WeatherApplication/Core/GameInstance/WeatherApplicationGameInstance.h>
#include <WeatherApplication/Network/NetworkManager/NetworkManager.h>
#include <WeatherApplication/Data/WeatherState.h>

void AWeatherSimulationHUD::BeginPlay()
{
	Super::BeginPlay();

	if (WeatherSimulationScreenAsset)
	{ 
		if (const auto PlayerController = GetWorld()->GetFirstPlayerController())
		{
			if (const auto WeatherDisplayController = Cast<AWeatherDisplayController>(PlayerController))
			{
				WeatherSimulationScreen = CreateWidget<UWeatherSimulationScreen>(WeatherDisplayController,WeatherSimulationScreenAsset);
				for (FString& CityName : CityNames)
				{
					UCityOption* CityOption = CreateWidget<UCityOption>(WeatherDisplayController,CityOptionAsset);
					CityOption->CustomInitialize(CityName);
					CityOption->AddToViewport();

					WeatherSimulationScreen->GetCityListContainer()->AddChild(CityOption);
				}
				WeatherSimulationScreen->AddToViewport();
			}
		}
	}
	if (const auto GameInstance = GetWorld()->GetGameInstance())
	{
		if (const auto WeatherApplicationGameInstanceClone = Cast<UWeatherApplicationGameInstance>(GameInstance))
		{
			WeatherApplicationGameInstance = WeatherApplicationGameInstanceClone;
			WeatherApplicationGameInstance->GetNetworkManager()->OnCurrentWeatherConditionResponseDelegate.AddUObject(this, &AWeatherSimulationHUD::OnCurrentWeatherObjectRecivedSucessfully);
		}
	}

}

void AWeatherSimulationHUD::OnCurrentWeatherObjectRecivedSucessfully(ACurrentWeatherConditionResponse* CurrentWeatherResponse)
{
	if (CurrentWeatherResponse)
	{
		if (WeatherSimulationScreen)
		{
			UpdateWeatherScreen(CurrentWeatherResponse->GetWeatherIcon() , CurrentWeatherResponse->GetWeatherText() , CurrentWeatherResponse->GetTemperature() , CurrentWeatherResponse->GetCurrentTime());
		}
	}
}

void AWeatherSimulationHUD::UpdateWeatherScreen(int16 WeatherID , const FString& InWeatherText , float InTemperature ,const FString& InCurrentClockTime)
{
	if (WeatherApplicationGameInstance)
	{
		if (const auto WeatherMap = WeatherApplicationGameInstance->GetWeatherDataTable())
		{
			FName RowName = FName(FString::FromInt(WeatherID));
			if (const FWeatherState* WeatherState = WeatherMap->FindRow<FWeatherState>(RowName, "CurrentWeatherCondition", true))
			{
				const FString TemperatureText = FString::Printf(TEXT("%.2f"), InTemperature);
				WeatherSimulationScreen->Update(InWeatherText, TemperatureText, WeatherState->WeatherIcon, InCurrentClockTime);
			}
		}	
	}
}

UWeatherSimulationScreen* AWeatherSimulationHUD::GetWeatherSimulationScreen() const
{
	return WeatherSimulationScreen;
}

void AWeatherSimulationHUD::TriggerRequestforCurrentWeather(const FString& CityName)
{
	if (auto World = GetWorld())
	{
		if (WeatherApplicationGameInstance)
		{
			if (auto NetworkManager = WeatherApplicationGameInstance->GetNetworkManager())
			{
				NetworkManager->InitiateRequestProcessing(CityName);
			}
		}
	}
}