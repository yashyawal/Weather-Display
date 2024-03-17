// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Http.h>
#include <HttpModule.h>
#include <HTTP/Public/Interfaces/IHttpRequest.h>
#include <HTTP/Public/Interfaces/IHttpResponse.h>
#include <WeatherApplication/Network/Request/NetworkRequestBase.h>
#include <WeatherApplication/Network/Request/GetCityCode.h>
#include <WeatherApplication/Network/Request/GetCurrentWeatherCondition.h>
#include <WeatherApplication/Network/Request/NetworkRequestBase.h>
#include <WeatherApplication/Network/Response/CurrentWeatherConditionResponse.h>
#include "NetworkManager.generated.h"
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurrentWeatherConditionResponse, ACurrentWeatherConditionResponse*);//Upon completion of response parse broadcast it to the WeatherManager

UCLASS()
class WEATHERAPPLICATION_API ANetworkManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetworkManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGetCityCode> GetCityCodeRequestAsset;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGetCurrentWeatherCondition> GetCurrentWeatherConditionRequestAsset;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACurrentWeatherConditionResponse> CurrentWeatherConditionResponseAsset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FOnCurrentWeatherConditionResponse OnCurrentWeatherConditionResponseDelegate;

	void InitiateRequestProcessing(const FString& City);
private:
	/*void OnGetCityKeyRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);*/
	
	//FString GetCityCode(const FString& INCityName);
	AGetCityCode* GetCityCodeRequest;
	AGetCurrentWeatherCondition* GetCurrentConditionRequest;
	ACurrentWeatherConditionResponse* CurrentWeatherConditionResponseObject;

	void OnGetCityIdSuccess(bool bWasSuccessful);
	void OnGetCurrentWeatherConditionSuccess(bool bWasSuccessful);

};
