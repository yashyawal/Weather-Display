// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WeatherSimulationHUD.generated.h"
class UWeatherSimulationScreen;
class UCityOption;
class ACurrentWeatherConditionResponse;
class UWeatherApplicationGameInstance;
/**
 *  Responsiible for Creating and diplaying UI on main weather simulation  
 */
UCLASS()
class WEATHERAPPLICATION_API AWeatherSimulationHUD : public AHUD
{
	GENERATED_BODY()
public:
	UWeatherSimulationScreen* GetWeatherSimulationScreen() const;
	void TriggerRequestforCurrentWeather(const FString& CityName);

protected:
	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWeatherSimulationScreen> WeatherSimulationScreenAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCityOption> CityOptionAsset;
    
	UPROPERTY(EditDefaultsOnly)
	TArray<FString> CityNames;

private:
	UWeatherSimulationScreen* WeatherSimulationScreen;
	UWeatherApplicationGameInstance* WeatherApplicationGameInstance;

	void OnCurrentWeatherObjectRecivedSucessfully(ACurrentWeatherConditionResponse* CurrentWeatherResponse);
	void UpdateWeatherScreen(int16 WeatherID , const FString& InWeatherText , float InTemperature , const FString& InCurrentTime);

};
