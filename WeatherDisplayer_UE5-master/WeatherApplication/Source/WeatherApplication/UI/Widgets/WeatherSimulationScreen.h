// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeatherSimulationScreen.generated.h"
class UButton;
class UImage;
class UTextBlock;
class UBackgroundBlur;
class UWidgetAnimation;
class UVerticalBox;
class UTexture2D;
/**
 * Responsible for holding ui components and events for simulating weather
 */
UCLASS()
class WEATHERAPPLICATION_API UWeatherSimulationScreen : public UUserWidget
{
	GENERATED_BODY()
public:
	UVerticalBox* GetCityListContainer() const;
	void Update(const FString& InWeatherText, const FString& InTemperature, UTexture2D* InWeatherIcon ,const FString& InCurrentClockTime);

protected:
    bool Initialize() override;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeatherText;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TemperatureText;

	UPROPERTY(meta = (BindWidget))
	UImage* WeatherIconImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentClockTime;

	UPROPERTY(meta = (BindWidgetAnim), transient)
	UWidgetAnimation* ShowCityListAnimation;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* CityListContainer;

private:
	UFUNCTION()
	void OnSettingButtonClicked();

};
