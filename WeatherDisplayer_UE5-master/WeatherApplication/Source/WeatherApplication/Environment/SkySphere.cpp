// Fill out your copyright notice in the Description page of Project Settings.


#include "SkySphere.h"

// Sets default values
ASkySphere::ASkySphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASkySphere::Update(double SunPitch)
{
	SunPitchRotation = SunPitch;
	UpdateSunAngle(SunPitch);
	RefreshSkyMaterial();
}

// Called when the game starts or when spawned
void ASkySphere::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle SkyUpdateTimerHandle;
	GetWorldTimerManager().SetTimer(SkyUpdateTimerHandle, this , &ThisClass::UpdateSunBySecond , 1.0f , true);
}

void ASkySphere::UpdateSunBySecond()
{
	constexpr const double DEGREE_PER_Second = 0.0041f;
	SunPitchRotation += DEGREE_PER_Second;
}


void ASkySphere::RefreshSkyMaterial_Implementation()
{
	// Has to be overwritten by skysphere Blueprint
}

void ASkySphere::UpdateSunAngle_Implementation(float InSunAngle)
{
	// Has to be overwritten by skysphere Blueprint 
}