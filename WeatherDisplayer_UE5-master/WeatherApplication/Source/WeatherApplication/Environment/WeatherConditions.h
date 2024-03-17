// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <NiagaraComponent.h>
#include "WeatherConditions.generated.h"

UCLASS()
class WEATHERAPPLICATION_API AWeatherConditions : public AActor
{
	GENERATED_BODY()	
public:
	AWeatherConditions();
protected:
	UPROPERTY(EditDefaultsOnly)
	uint32 Density;

	UPROPERTY(EditDefaultsOnly)
	float ParticleScale; // 0-1

	UPROPERTY(EditDefaultsOnly)
	FString WeatherStateName;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UNiagaraComponent* NiagraSystem;//replace with niagra system

public:	
	void Initialize();

};
