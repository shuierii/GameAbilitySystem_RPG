// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AuraAIController.generated.h"

class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class GAS_RPG_API AAuraAIController : public AAIController
{
	GENERATED_BODY()

public:
	AAuraAIController();

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
