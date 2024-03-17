// Fill out your copyright notice in the Description page of Project Settings.
#include "WeatherManager.h"
#include <WeatherApplication/Environment/WeatherConditions.h>
#include <WeatherApplication/Network/NetworkManager/NetworkManager.h>
#include <Kismet/GameplayStatics.h>
#include <WeatherApplication/Environment/SkySphere.h>
#include <WeatherApplication/Core/GameInstance/WeatherApplicationGameInstance.h>
#include <Engine/DataTable.h>
#include <WeatherApplication/Data/WeatherState.h>

// Sets default values
AWeatherManager::AWeatherManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AWeatherConditions* AWeatherManager::GetWeatherComponent(EWeatherComponent WeatherComponentIndex) const
{
	return WeatherComponentsCache[WeatherComponentIndex];
}

void AWeatherManager::OnCurrentWeatherConditionParsedSuccessfully(ACurrentWeatherConditionResponse* WeatherResponseObject)
{
	if (WeatherResponseObject)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("%s"), *WeatherResponseObject->GetActorNameOrLabel());
		// calulate the sun pitch with time from response obejct
		UpdateSunRotation(WeatherResponseObject->GetCurrentTime());
		// access the datatable using the weather icon id then activate and deactivate the weathercomponents in weathercomponentscache 
		UpdateWeather(WeatherResponseObject->GetWeatherIcon());
	}
}

// Called when the game starts or when spawned
void AWeatherManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> SkySphereArray;
	if (auto World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(World, ASkySphere::StaticClass(), SkySphereArray);
		if (SkySphereArray.Num())
		{
			SkySphere = Cast<ASkySphere>(SkySphereArray[0]);
		}
		if (WeatherComponentsAssets.Num() > 0)
		{
			WeatherComponentsCache.Add(EWeatherComponent::ECLOUD, World->SpawnActor<AWeatherConditions>(WeatherComponentsAssets[EWeatherComponent::ECLOUD], FVector(0, 0, 900), FRotator::ZeroRotator))->SetActorHiddenInGame(true);
			WeatherComponentsCache.Add(EWeatherComponent::ERAIN, World->SpawnActor<AWeatherConditions>(WeatherComponentsAssets[EWeatherComponent::ERAIN], FVector(0, 0, 900), FRotator::ZeroRotator))->SetActorHiddenInGame(true);
			WeatherComponentsCache.Add(EWeatherComponent::ETHUNDER, World->SpawnActor<AWeatherConditions>(WeatherComponentsAssets[EWeatherComponent::ETHUNDER], FVector(0, 0, 900), FRotator::ZeroRotator))->SetActorHiddenInGame(true);
			WeatherComponentsCache.Add(EWeatherComponent::ESNOW, World->SpawnActor<AWeatherConditions>(WeatherComponentsAssets[EWeatherComponent::ESNOW], FVector(0, 0, 900), FRotator::ZeroRotator))->SetActorHiddenInGame(true);
		}

		if (auto GameInstance = Cast<UWeatherApplicationGameInstance>(World->GetGameInstance()))
		{
			GameInstance->GetNetworkManager()->OnCurrentWeatherConditionResponseDelegate.AddUObject(this, &AWeatherManager::OnCurrentWeatherConditionParsedSuccessfully);
		}
	}
}

// Called every frame
void AWeatherManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeatherManager::UpdateSunRotation(const FString& CurrentTime)
{
	int16 Hours, Minutes, Seconds;
	Hours = FCString::Atoi(*CurrentTime.Mid(0, 2));
	Minutes = FCString::Atoi(*CurrentTime.Mid(3, 2));
	Seconds = FCString::Atoi(*CurrentTime.Mid(6, 2));
	constexpr const double DEGREE_PER_HOUR = 15.0f;
	constexpr const double DEGREE_PER_Minute = 0.25f;
	constexpr const double DEGREE_PER_Second = 0.0041f;
	constexpr const double PITCH_ON_MIDNIGHT = 90.0f;

	float SunPitch = PITCH_ON_MIDNIGHT + (Hours * DEGREE_PER_HOUR) + (Minutes * DEGREE_PER_Minute) + (Seconds * DEGREE_PER_Second);
	if (SkySphere)
	{
		SkySphere->Update(SunPitch);
	}
}

void AWeatherManager::UpdateWeather(int16 WeatherID)
{
	if (const auto GameInstance = GetWorld()->GetGameInstance())
	{
		if (const auto WeatherApplicationGameInstance = Cast<UWeatherApplicationGameInstance>(GameInstance))
		{
			if (const auto WeatherMap = WeatherApplicationGameInstance->GetWeatherDataTable())
			{
				FName RowName = FName(FString::FromInt(WeatherID));
				if (const FWeatherState* WeatherState = WeatherMap->FindRow<FWeatherState>(RowName, "CurrentWeatherCondition", true))
				{
					// Inactive all weather components prior to activating newer weather components 
					InactiveAllWeatherComponents();

					for (EWeatherComponent WeatherComponent : WeatherState->WetherComponentList)
					{
						switch (WeatherComponent)
						{
						case ECLOUD:
						{
							WeatherComponentsCache[EWeatherComponent::ECLOUD]->SetActorHiddenInGame(false);
							break;
						}
						case ERAIN:
						{
							WeatherComponentsCache[EWeatherComponent::ERAIN]->SetActorHiddenInGame(false);
							break;
						}
						case ESNOW:
						{
							WeatherComponentsCache[EWeatherComponent::ESNOW]->SetActorHiddenInGame(false);
							break;
						}
						case ETHUNDER:
						{
							WeatherComponentsCache[EWeatherComponent::ETHUNDER]->SetActorHiddenInGame(false);
							break;
						}
						default:
							break;
						}
					}
				}
			}
		}
	}
}

void AWeatherManager::InactiveAllWeatherComponents()
{
	for (auto WeatherComponent : WeatherComponentsCache)
	{
		WeatherComponent.Value->SetActorHiddenInGame(true);
	}
}
