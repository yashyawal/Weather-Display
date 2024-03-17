// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"
#include "Serialization/JsonSerializer.h"
// Sets default values
ANetworkManager::ANetworkManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANetworkManager::BeginPlay()
{
	Super::BeginPlay();
	if (UWorld* World = GetWorld())
	{
		GetCityCodeRequest = Cast<AGetCityCode>(World->SpawnActor(GetCityCodeRequestAsset));
		GetCurrentConditionRequest = Cast<AGetCurrentWeatherCondition>(World->SpawnActor(GetCurrentWeatherConditionRequestAsset));
		CurrentWeatherConditionResponseObject = Cast<ACurrentWeatherConditionResponse>(World->SpawnActor(CurrentWeatherConditionResponseAsset));
	}
	// For Temporary purpose TODO: Create UI for triggering the request 
	GetCityCodeRequest->OnProcessRequestCompleteDelegate.AddUObject(this, &ANetworkManager::OnGetCityIdSuccess);
	GetCurrentConditionRequest->OnProcessRequestCompleteDelegate.AddUObject(this, &ANetworkManager::OnGetCurrentWeatherConditionSuccess);
}

// Called every frame
void ANetworkManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANetworkManager::InitiateRequestProcessing(const FString& City)
{
	GetCityCodeRequest->ProcessGetRequest(City);
}

void ANetworkManager::OnGetCityIdSuccess(bool bWasSuccessful)
{
	TArray<TSharedPtr<FJsonValue>>& ResponseString = GetCityCodeRequest->GetResposeArray();
	if (ResponseString.Num()>0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%d"), ResponseString[0]->AsObject()->HasField("Key"));
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *);
		FString CityCodeKey = ResponseString[0]->AsObject()->GetStringField("Key");
		GetCurrentConditionRequest->ProcessGetRequest(CityCodeKey);
	}
}

void ANetworkManager::OnGetCurrentWeatherConditionSuccess(bool bWasSuccessful)
{
	TArray<TSharedPtr<FJsonValue>>& ResponseString = GetCurrentConditionRequest->GetResposeArray();
	if (ResponseString.Num() > 0)
	{
		FString CurrentDateTime = ResponseString[0]->AsObject()->GetStringField("LocalObservationDateTime");
		FString CurrentClockTime = CurrentDateTime.Mid(11, 8);
		FString WeatherText = ResponseString[0]->AsObject()->GetStringField("WeatherText");
		int16 WeatherIcon = ResponseString[0]->AsObject()->GetIntegerField("WeatherIcon");
		bool bIsDayTime = ResponseString[0]->AsObject()->GetBoolField("IsDayTime");
		TSharedPtr<FJsonObject> Temperature = ResponseString[0]->AsObject()->GetObjectField("Temperature");
		TSharedPtr<FJsonObject> Metric = Temperature->GetObjectField("Metric");
		float TemperatureInCelcius = Metric->GetNumberField("Value");
		//UE_LOG(LogTemp, Warning, TEXT("%s , %d , %d , %f , %s "), *WeatherText , WeatherIcon , bIsDayTime , TemperatureInCelcius , *CurrentClockTime);
		CurrentWeatherConditionResponseObject->SetValues(WeatherText, WeatherIcon, bIsDayTime, TemperatureInCelcius , CurrentClockTime);
		OnCurrentWeatherConditionResponseDelegate.Broadcast(CurrentWeatherConditionResponseObject);
	}
}
