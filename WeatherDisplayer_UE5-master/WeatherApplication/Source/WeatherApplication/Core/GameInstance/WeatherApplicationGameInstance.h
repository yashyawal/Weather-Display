// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WeatherApplicationGameInstance.generated.h"
class AWeatherManager;
class ANetworkManager;
class UDataTable;
/**
 *  Global instance to store global states and classes for Weather application
 */
UCLASS()
class WEATHERAPPLICATION_API UWeatherApplicationGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	AWeatherManager* GetWeatherManager() const;
	ANetworkManager* GetNetworkManager() const;
	UDataTable* GetWeatherDataTable() const;

protected:
	virtual void Init() override;
    
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeatherManager> WeatherManagerAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ANetworkManager> NetworkManagerAsset;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* WeatherDataTableAsset;

private:
	UPROPERTY(VisibleAnywhere)
	AWeatherManager* WeatherManager;

	UPROPERTY(VisibleAnywhere)
	ANetworkManager* NetworkManager;

};
