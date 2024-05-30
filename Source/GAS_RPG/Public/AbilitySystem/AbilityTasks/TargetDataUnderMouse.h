// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignatue, const FVector&, Data);

/**
 * 
 */
UCLASS()
class GAS_RPG_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", DisplayName = "TargetDataUnderMouse", meta = ( HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	virtual void Activate() override;
	
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignatue ValidData;
};
