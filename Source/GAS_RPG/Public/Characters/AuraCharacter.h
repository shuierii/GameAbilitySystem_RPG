// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void InitializeDefaultAttributes() override;

	//** combat interface */
	virtual void AddToXP_Implementation(int32 InXP) override;
	//** end combat interface */
	
	//** combat interface */
	virtual int32 GetPlayerLevel_Implementation() override;
	//** end combat interface */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultMainAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultResistanceAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

private:
	// 依赖设置
	virtual void InitAbilityActorInfo() override;
};
