// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

UCLASS()
class GAS_RPG_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAuraEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
};
