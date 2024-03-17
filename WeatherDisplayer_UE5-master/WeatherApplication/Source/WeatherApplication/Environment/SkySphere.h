// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkySphere.generated.h"

UCLASS()
class WEATHERAPPLICATION_API ASkySphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkySphere();
	void Update(double SunPitch);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	void UpdateSunAngle(float InSunAngle);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RefreshSkyMaterial();
	
private:
	UPROPERTY(VisibleAnywhere)
	float SunPitchRotation;

	UFUNCTION()
	void UpdateSunBySecond();

};
