// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Characters/AuraCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
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

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	virtual void InitializeDefaultAttributes() override;
	
private:
	virtual void InitAbilityActorInfo() override;
};
