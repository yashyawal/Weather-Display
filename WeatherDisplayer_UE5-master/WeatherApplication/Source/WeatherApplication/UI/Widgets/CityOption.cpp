#include "CityOption.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <WeatherApplication/Player/WeatherDisplayController.h>
#include <WeatherApplication/UI/HUD/WeatherSimulationHUD.h>

bool UCityOption::Initialize()
{
	if (Super::Initialize())
	{
		if (OptionButton)
		{
			OptionButton->OnClicked.AddDynamic(this, &ThisClass::OnOptionButtonClicked);
		}
		return true;
	}
	return false;
}

void UCityOption::OnOptionButtonClicked()
{
	if (const auto PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (const auto WeatherDisplayController = Cast<AWeatherDisplayController>(PlayerController))
		{
			if (auto WeatherSimulatorHUD = Cast<AWeatherSimulationHUD>(WeatherDisplayController->GetHUD()))
			{
				WeatherSimulatorHUD->TriggerRequestforCurrentWeather(CityName);
			}
		}
	}
}
UButton* UCityOption::GetOptionButton() const
{
	return OptionButton;
}

void UCityOption::CustomInitialize(const FString& InCityName)
{
	if (UTextBlock* ButtonText = Cast<UTextBlock>(OptionButton->GetChildAt(0)))
	{
		ButtonText->SetText(FText::FromString(InCityName));
	}
	CityName = InCityName;
}
