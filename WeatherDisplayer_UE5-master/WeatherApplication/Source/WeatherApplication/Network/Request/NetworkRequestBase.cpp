// Fill out your copyright notice in the Description page of Project Settings.
#include "NetworkRequestBase.h"

ANetworkRequestBase::ANetworkRequestBase()
{
}

ANetworkRequestBase::~ANetworkRequestBase()
{
}

void ANetworkRequestBase::OnProcessRequestComplete(FHttpRequestPtr InRequest, FHttpResponsePtr OutResponse, bool bConnectedSuccessfully)
{
	//if the query is successful
	if (OutResponse->GetResponseCode() == 200)
	{
		const FString ResponseString = OutResponse->GetContentAsString();
		if (ResponseString.Len())
		{
			TArray<TSharedPtr<FJsonValue>> OutArray;
			TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseString);
			FJsonSerializer::Deserialize(JsonReader, OutArray);
			ResponseArray = OutArray;
			OnProcessRequestCompleteDelegate.Broadcast(true);
		}
	}
}

void ANetworkRequestBase::ProcessGetRequest(const FString& RequestString)
{
		if (auto Http = &FHttpModule::Get())
		{
			TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();;
			//TODO : Replace the key and city name with it's own fields which can be configured (Mostly city ) by the player
			Request->SetURL(RequestString);
			Request->SetVerb("GET");
			Request->SetHeader("Content-Type", "application/json");
			Request->OnProcessRequestComplete().BindUObject(this, &ANetworkRequestBase::OnProcessRequestComplete);
			Request->ProcessRequest();
		}
}

TArray<TSharedPtr<FJsonValue>>& ANetworkRequestBase::GetResposeArray()
{
	return ResponseArray;
}
