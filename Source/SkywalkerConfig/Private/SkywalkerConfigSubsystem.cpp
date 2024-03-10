// Fill out your copyright notice in the Description page of Project Settings.

#include "SkywalkerConfigSubsystem.h"

#include "Engine/AssetManager.h"

DEFINE_LOG_CATEGORY_STATIC(SkywalkerConfig, Log, All);

bool USkywalkerConfigSubsystem::LoadDataTableAsset(const TArray<FAssetData>& ArrayAssetData)
{
	LoadFinish = false;

	TArray<FSoftObjectPath> TArrayTableDataPath;
	for (int32 i = 0; i < ArrayAssetData.Num(); ++i)
	{
		TArrayTableDataPath.AddUnique(ArrayAssetData[i].ToSoftObjectPath());
	}

	//ResourceManager->LoadAsync(TArrayTableDataPath);

	FStreamableManager& Streamable = UAssetManager::Get().GetStreamableManager();
	StreamableHandle = Streamable.RequestAsyncLoad(TArrayTableDataPath, FStreamableDelegate::CreateUObject(this, &USkywalkerConfigSubsystem::DataTableAssetLoadComplete));

	return true;
}

bool USkywalkerConfigSubsystem::IsLoadFinish()
{
	return LoadFinish;
}

void USkywalkerConfigSubsystem::DataTableAssetLoadComplete()
{
	TArray<UObject*> OutObjects;
	StreamableHandle->GetLoadedAssets(OutObjects);
	for (int32 i = 0; i < OutObjects.Num(); ++i)
	{
		UE_LOG(SkywalkerConfig, Warning, TEXT("Name::::::::%s"), *OutObjects[i]->GetName());

		TSortedMapNameToUDataTable.Add(OutObjects[i]->GetName(), Cast<UDataTable>(OutObjects[i]));
	}

	LoadFinish = true;
}

UDataTable* USkywalkerConfigSubsystem::GetDataTable(FString inName)
{
	//UE_LOG(ETDConfigSubsystem, Log, TEXT("GetDataTable \"%s\""), *inName);

	UDataTable* DataTable = *TSortedMapNameToUDataTable.Find(inName);
	if (nullptr != DataTable)
	{
		return DataTable;
	}

	UE_LOG(SkywalkerConfig, Error, TEXT("GetDataTable \"%s\" FAILED"), *inName);

	return nullptr;
}
