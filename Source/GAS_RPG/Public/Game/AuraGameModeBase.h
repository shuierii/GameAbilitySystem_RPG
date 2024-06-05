// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Info")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
