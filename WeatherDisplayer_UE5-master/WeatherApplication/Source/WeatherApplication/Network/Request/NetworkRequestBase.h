// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Http.h>
#include <HttpModule.h>
#include <HTTP/Public/Interfaces/IHttpRequest.h>
#include <HTTP/Public/Interfaces/IHttpResponse.h>
#include "NetworkRequestBase.generated.h"
DECLARE_MULTICAST_DELEGATE_OneParam(FOnProcessRequestComplete, bool);
/**
 * BaseClass holds common functions and properties for all rquest objects inheriting from it .
 */
UCLASS()
class WEATHERAPPLICATION_API ANetworkRequestBase:public AActor
{
	GENERATED_BODY()

public:
	ANetworkRequestBase();
	~ANetworkRequestBase();
	virtual void ProcessGetRequest(const FString& RequestString);
	FOnProcessRequestComplete OnProcessRequestCompleteDelegate;
	TArray<TSharedPtr<FJsonValue>>& GetResposeArray();


protected:
	TArray<TSharedPtr<FJsonValue>> ResponseArray;

	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	UPROPERTY(EditDefaultsOnly)
	FString RequestURL;

};
