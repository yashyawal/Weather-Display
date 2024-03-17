// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherManager.generated.h"
class AWeatherConditions;
class ASkySphere;
class ACurrentWeatherConditionResponse;
enum  EWeatherComponent;
UCLASS()
class WEATHERAPPLICATION_API AWeatherManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeatherManager();
	AWeatherConditions* GetWeatherComponent(EWeatherComponent WeatherComponentIndex) const;

	void OnCurrentWeatherConditionParsedSuccessfully(ACurrentWeatherConditionResponse* WeatherResponseObject);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TMap<TEnumAsByte<EWeatherComponent>,TSubclassOf<AWeatherConditions>> WeatherComponentsAssets;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TMap<TEnumAsByte<EWeatherComponent>, AWeatherConditions*> WeatherComponentsCache;
	ASkySphere* SkySphere;

	void UpdateSunRotation(const FString& CurrentTime);//in pitch
	void UpdateWeather(int16 WeatherID);

	void InactiveAllWeatherComponents();
};
