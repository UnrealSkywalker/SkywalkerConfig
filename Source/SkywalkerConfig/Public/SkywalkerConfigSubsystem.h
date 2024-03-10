// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Containers/SortedMap.h"
#include "Engine/Datatable.h"
#include "Engine/StreamableManager.h"

#include "SkywalkerConfigSubsystem.generated.h"

/**
 *
 */
UCLASS()
class SKYWALKERCONFIG_API USkywalkerConfigSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UDataTable* GetDataTable(FString inName);

	UFUNCTION(BlueprintCallable, Category = "ETDConfig")
	bool LoadDataTableAsset(const TArray<FAssetData>& ArrayAssetData);

	UFUNCTION(BlueprintCallable, Category = "ETDConfig")
	bool IsLoadFinish();

protected:
	void DataTableAssetLoadComplete();

private:
	TSortedMap<FString, UDataTable*> TSortedMapNameToUDataTable;

	bool LoadFinish;

	TSharedPtr<FStreamableHandle> StreamableHandle;
};
