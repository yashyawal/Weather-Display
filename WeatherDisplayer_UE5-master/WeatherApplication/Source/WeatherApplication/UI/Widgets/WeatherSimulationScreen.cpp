// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherSimulationScreen.h"
#include <Components/Button.h>
#include <Components/Image.h>
#include <Components/BackgroundBlur.h>
#include <Animation/WidgetAnimation.h>
#include <Components/TextBlock.h>
#include <Engine/Texture2D.h>

UVerticalBox* UWeatherSimulationScreen::GetCityListContainer() const
{
	return CityListContainer;
}
void UWeatherSimulationScreen::Update(const FString& InWeatherText, const FString& InTemperature, UTexture2D* InWeatherIcon , const FString& InCurrentClockTime)
{
	if (WeatherText)
	{
		WeatherText->SetText(FText::FromString(InWeatherText));
	}
	if (TemperatureText)
	{
		TemperatureText->SetText(FText::FromString(InTemperature));
	}
	if (WeatherIconImage)
	{
		WeatherIconImage->Brush.SetResourceObject(InWeatherIcon);
	}
	if (CurrentClockTime)
	{
		CurrentClockTime->SetText(FText::FromString(InCurrentClockTime));
	}

}
bool UWeatherSimulationScreen::Initialize()
{
	if (Super::Initialize())
	{
		if (SettingButton)
		{
			SettingButton->OnClicked.AddDynamic(this, &ThisClass::OnSettingButtonClicked);
		}
		return true;
	}
	return false;
}

void UWeatherSimulationScreen::OnSettingButtonClicked()
{
	PlayAnimation(ShowCityListAnimation);
}
