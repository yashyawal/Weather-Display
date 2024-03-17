// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherConditions.h"

AWeatherConditions::AWeatherConditions()
{
	NiagraSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagraComponent"));
	NiagraSystem->SetupAttachment(RootComponent);
}

void AWeatherConditions::Initialize()
{
	// TODO : Apply the preset settings from the component it self  to the corresponding particle system

}
