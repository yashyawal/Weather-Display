// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CityOption.generated.h"
class UButton;
/**
 * Represents a city option widget 
 */
UCLASS()
class WEATHERAPPLICATION_API UCityOption : public UUserWidget
{
	GENERATED_BODY()
public:
	UButton* GetOptionButton() const;
	void CustomInitialize(const FString& InCityName);
protected:
	bool Initialize() override;

	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton;


private:
	UFUNCTION()
	void OnOptionButtonClicked();

	FString CityName;
};
