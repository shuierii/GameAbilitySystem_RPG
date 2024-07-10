// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LootTiers.generated.h"

USTRUCT(BlueprintType)
struct FLootItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "LootTiers")
	TSubclassOf<AActor> LootClass;

	UPROPERTY(EditAnywhere, Category= "LootTiers")
	float ChanceToSpawn = 0.f;

	UPROPERTY(EditAnywhere, Category= "LootTiers")
	int32 MaxNumberToSpawn = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "LootTiers")
	bool bLootLevelOverride = true;
};

/**
 * 
 */
UCLASS()
class GAS_RPG_API ULootTiers : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<FLootItem> GetLootItems();

	UPROPERTY(EditDefaultsOnly, Category= "LootTiers")
	TArray<FLootItem> LootItems;
};
