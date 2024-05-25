// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API AEnemyCharacter : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	//** enemy interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//** end enemy interface */

	//** combat interface */
	virtual int32 GetPlayerLevel() override;
	//** end combat interface */

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

protected:
	virtual void BeginPlay() override;

private:
	virtual void InitAbilityActorInfo() override;
};
